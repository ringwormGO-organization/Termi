/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Implementation of helper functions (e.g. functions to load function from dynamic library)
*/

#include "Export.h"

#include <stdarg.h>

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
    #include <libloaderapi.h>

#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
    #include <dlfcn.h>
#endif

#if defined _WIN32 || defined _WIN64
    #pragma warning(disable: 4996)
    #pragma comment(lib, "Advapi32.lib")
    #pragma comment(lib, "Kernel32.lib")

    template <typename T>
    int LoadDynamicLibrary(const char* path, const char* function, T argument)
    {
        typedef int(__cdecl* MYPROC)(T);

        HINSTANCE hinstLib;
        MYPROC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module
        hinstLib = LoadLibrary(LPCSTR(path));

        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (MYPROC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(argument);
            }

            else
            {
                printf("Error loading function '%s' from '%s'!\n", function, path);
                return 1;
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Error loading function '%s' from '%s'!\n", function, path);
            return 1;
        }

        return 0;
    }

    // This explicit template instantiation is making `LoadDynamicLibrary` function available from extern "C" block
    template int LoadDynamicLibrary<const char*>(const char* path, const char* function, const char* argument);

    const char* OperatingSystem()
    {
        OSVERSIONINFO vi;
        vi.dwOSVersionInfoSize = sizeof(vi);
        if (GetVersionEx(&vi) == 0)
        {
            return 0;
        }

        switch (vi.dwPlatformId)
        {
            case VER_PLATFORM_WIN32s:
                return "Windows 3.x";
            case VER_PLATFORM_WIN32_WINDOWS:
                return vi.dwMinorVersion == 0 ? "Windows 95" : "Windows 98";
            case VER_PLATFORM_WIN32_NT:
                return "Windows NT";
            default:
                return "Unknown";
        }
    }

    uint64_t UptimeS()
    {
        return GetTickCount64() / 1000;
    }

    uint64_t UptimeM()
    {
        return GetTickCount64() / 60000;
    }

    uint64_t UptimeH()
    {
        return GetTickCount64() / 3600000;
    }

#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
    template <typename T>
    int LoadDynamicLibrary(const char* path, const char* function, T argument)
    {
        void *handle;
        void (*func)(T);
        char *error;

        handle = dlopen(path, RTLD_LAZY);
        if (!handle) 
        {
            fputs (dlerror(), stderr);
            puts(" ");

            return 1;
        }

        func = reinterpret_cast<void (*)(T)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)
        {
            fputs(error, stderr);
            return 1;
        }

        (*func)(argument);
        dlclose(handle);

        return 0;
    }

    // This explicit template instantiation is making `LoadDynamicLibrary` function available from extern "C" block
    template int LoadDynamicLibrary<const char*>(const char* path, const char* function, const char* argument);
#endif

void AddLog(std::string fmt, ...)
{
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
    buf[sizeof(buf) - 1] = 0;
    va_end(args);

    LoadDynamicLibrary(GUI_PATH, "AddLog", buf);
}

void Status(int error_code)
{
    switch (error_code)
    {
    case 0:
        AddLog("$g\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Successfully executed!");
        break;

    case 1:
        AddLog("$b\t\t\t\t\t\t\t\t\t\t\t\t Not successfully executed, user error!");
        break;

    case 2: /* system error */
        AddLog("$r\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Not successfully executed, system error!");
        break;
    }
}
