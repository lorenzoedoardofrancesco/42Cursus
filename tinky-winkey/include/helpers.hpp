#pragma once

#include <filesystem>
#include <mutex>
#include <print>

#include <Windows.h>

#include "config.hpp"

/* ═════════════════════════════════════════════════════════════════════
   Logging Functions
═════════════════════════════════════════════════════════════════════ */

namespace std
{
template <>
struct formatter<std::filesystem::path, char> : formatter<std::string_view>
{
    [[maybe_unused]] auto format(const std::filesystem::path& p, format_context& ctx) const { return formatter<std::string_view>::format(p.string(), ctx); }
};
}

static std::mutex gLogMutex;

template <typename... Args>
void LogTo(std::ostream& os, FILE* console, std::string_view prefix, std::string_view newline, std::format_string<Args...> fmt, Args&&... args)
{
    auto formatted = std::format(fmt, std::forward<Args>(args)...);
    std::scoped_lock lk(gLogMutex);
    std::print(console, "{}{}", formatted, newline);
    if (os) os << prefix << formatted << newline << std::flush;
}

template <typename... Args>
void KeyLog(std::format_string<Args...> fmt, Args&&... args)
{
    LogTo(gConfig.KeylogFile, stdout, "", "", fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void LogInfo(std::format_string<Args...> fmt, Args&&... args)
{
    LogTo(gConfig.DebugLogFile, stdout, "[Info] ", "\n", fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void LogErr(std::format_string<Args...> fmt, Args&&... args)
{
    LogTo(gConfig.DebugLogFile, stderr, "[Error] ", "\n", fmt, std::forward<Args>(args)...);
}

/* ═════════════════════════════════════════════════════════════════════
   String Manipulation Functions
═════════════════════════════════════════════════════════════════════ */
std::filesystem::path JoinPath(std::filesystem::path dir, std::filesystem::path file);
std::string           ToLower(std::string str);
std::string           ToUtf8(const WCHAR* wstr);
std::wstring          ToUtf16(const CHAR* str);
std::string           TranslateKeyToUtf8(DWORD vkCode, DWORD scanCode);

/* ═════════════════════════════════════════════════════════════════════
   Helper Functions
═════════════════════════════════════════════════════════════════════ */

template <int I>
int PrintLastError(std::string_view context)
{
    DWORD errorCode = GetLastError();

    char*      messageBuffer = nullptr;
    const auto size          = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, errorCode, 0,
                                             reinterpret_cast<LPSTR>(&messageBuffer), 0, nullptr);

    auto message = size ? std::string(messageBuffer, size) : "Unknown error";
    LocalFree(messageBuffer);

    while (!message.empty() && std::isspace(static_cast<unsigned char>(message.back()))) message.pop_back();

    LogErr("{} failed ({}): {}", context, errorCode, message);

    return I;
}

std::filesystem::path GetExeDir();
std::filesystem::path GetLogDir();

std::string GetActiveWindowTitle();
std::string GetActiveProcessName();
std::string GetActiveUsername();

enum TimestampType : uint8_t { Filename, LogEntry };

template <TimestampType Type>
std::string GetTimestamp()
{
    SYSTEMTIME st;
    GetLocalTime(&st);

    return Type == LogEntry ? std::format("[{:02}.{:02}.{} {:02}:{:02}:{:02}]", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond)
                            : std::format("{:02}{:02}{}_{:02}{:02}{:02}", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
}

/* ═════════════════════════════════════════════════════════════════════
   RAII Helpers
═════════════════════════════════════════════════════════════════════ */

template <class R, auto CloseFn>
class RAII
{
public:
    explicit RAII(R r = {}) : handle(r) {}

    RAII(const RAII& other)                = delete;
    RAII(RAII&& other) noexcept            = delete;
    RAII& operator=(const RAII& other)     = delete;
    RAII& operator=(RAII&& other) noexcept = delete;

    ~RAII()
    {
        if (handle) CloseFn(handle);
    }

    R get() const { return handle; }

    void reset(R r = {}) noexcept
    {
        if (handle) CloseFn(handle);
        handle = r;
    }

    explicit operator bool() const { return handle != nullptr; }

private:
    R handle{};
};

using HHook              = RAII<HHOOK, &UnhookWindowsHookEx>;
using Handle             = RAII<HANDLE, CloseHandle>;
using ScHandle           = RAII<SC_HANDLE, CloseServiceHandle>;
using ProcessInformation = RAII<PROCESS_INFORMATION*, [](PROCESS_INFORMATION* pi) {
    if (!pi) return;
    if (pi->hProcess) CloseHandle(pi->hProcess);
    if (pi->hThread) CloseHandle(pi->hThread);
    delete pi;
}>;