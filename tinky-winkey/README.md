# tinky-winkey

## Introduction

The *tinky-winkey* project is an introduction to Windows internals through the development of a **Windows service** and a **keylogger**, written in **C++20**. The project covers the Windows Service Control Manager (SCM), low-level keyboard hooking, SYSTEM token impersonation, and process launching across user sessions. You can find the project description in the [PDF available in this repository](https://github.com/lorenzoedoardofrancesco/42Cursus/raw/main/tinky-winkey/tinky-winkey.pdf).

> This project was developed strictly as a security research exercise within the **Ecole 42** curriculum.

## Architecture

The project is composed of two executables:

### `svc.exe` — Windows Service

The service program (`tinky`) manages the keylogger lifecycle through the SCM:

```
svc.exe install    # Register the service
svc.exe start      # Start the service (launches winkey.exe)
svc.exe stop       # Stop the service (kills winkey.exe)
svc.exe delete     # Remove the service
```

On start, the service:
1. Enables `SE_INCREASE_QUOTA`, `SE_ASSIGNPRIMARYTOKEN`, and `SE_TCB` privileges
2. Duplicates the SYSTEM token and sets the active console session ID
3. Launches the keylogger in the user session via `CreateProcessAsUser`

### `winkey.exe` — Keylogger

The keylogger captures keyboard input using a low-level hook (`WH_KEYBOARD_LL`) and logs keystrokes in a human-readable format to `winkey.log`. It tracks:

- Foreground window title and process name
- Timestamps for each window switch
- Keystroke translation respecting the current keyboard locale
- Modifier keys (Ctrl, Alt, Shift, Win) and special keys

## Features

### Mandatory

- Windows service with install/start/stop/delete lifecycle
- SYSTEM token impersonation to launch the keylogger
- Single-instance enforcement via a global mutex
- Low-level keyboard hook with locale-aware keystroke logging
- Per-window timestamps with process name tracking

### Bonus

- **Process hiding** — renames executables with zero-width Unicode characters and manipulates DACLs to hide the service from `sc.exe` and `tasklist`
- **Clipboard logging** — captures clipboard content on Ctrl+C/Ctrl+X
- **Screen capture** — periodic screenshots at configurable intervals
- **Microphone capture** — timed audio recording via the Windows Multimedia API
- **Application/User filtering** — configurable whitelist of monitored apps and users
- **Masked input capture** — detects password fields and captures text behind input masks
- **Remote shell** — reverse TCP shell for remote access

## Configuration

All features are driven by an INI config file (`config.ini`) loaded at startup:

```ini
DebugMode=true
HideProcess=false
ClipboardLogging=true
ScreenCapture=true
ScreenshotIntervalSec=1
MicrophoneCapture=false
MicrophoneDurationSec=10
MaskedCapture=true
RemoteShell=false
RemoteIp=42.42.42.42
RemotePort=4242
MonitoredApps=chrome,firefox,code
MonitoredUsers=
```

## Compilation

The project must be compiled on **Windows** using the MSVC toolchain:

```bash
nmake
```

This produces `out\svc.exe` and `out\winkey.exe`.

## Technical Summary

- **Language:** C++20 (MSVC with `/std:c++latest`)
- **Compiler:** `cl` with `/Wall /WX`
- **Build system:** `nmake`
- **RAII wrappers** for all Windows handles (`HANDLE`, `SC_HANDLE`, `HHOOK`, `PROCESS_INFORMATION`)
- **Windows APIs:** SCM, `SetWindowsHookEx`, `DuplicateTokenEx`, `CreateProcessAsUser`, `WTSGetActiveConsoleSessionId`
- **Thread-safe logging** with `std::mutex` and `std::jthread` for background tasks
