#include <iostream>

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
#elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__
    #include <dlfcn.h>
#endif

/* -------------------------- */

#if defined _WIN32 || defined _WIN64
    /* Returns the last Win32 error, in string format. Returns an empty string if there is no error. */
    std::string GetLastErrorAsString()
    {
        /* Get the error message ID, if any. */
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0) {
            return std::string(); /* no error message has been recorded */
        }

        LPSTR messageBuffer = nullptr;

        /* Ask Win32 to give us the string version of that message ID. */
        /* The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be). */
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        /* Copy the error message into a std::string. */
        std::string message(messageBuffer, size);

        /* Free the Win32's string's buffer. */
        LocalFree(messageBuffer);

        return message;
    }

    void LoadDynamicLibrary(const char* path, const char* function)
    {
        typedef int(__cdecl* FUNC)(int);

        HINSTANCE hinstLib;
        FUNC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        /* Get a handle to the DLL module. */
        hinstLib = LoadLibrary(LPCSTR(path));

        /* If the handle is valid, try to get the function address. */
        if (hinstLib != NULL)
        {
            ProcAdd = (FUNC)GetProcAddress(hinstLib, function);

            /* If the function address is valid, call the function. */
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(12);
            }

            /* Free the DLL module. */
            fFreeResult = FreeLibrary(hinstLib);
        }

        /* If unable to call the DLL function, use an alternative. */
        if (!fRunTimeLinkSuccess)
        {
            printf("Failed to run function from executable!\n");
            printf("%d\n", GetLastError());
            std::cout << GetLastErrorAsString() << std::endl << std::endl;
        }
    }
#elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__
    void LoadDynamicLibrary(const char* path, const char* function)
    {
        void *handle;
        void (*func)(int);
        char *error;

        handle = dlopen (path, RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(int)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(12); /* ignore this argument */
        dlclose(handle);
    }
#endif

int main()
{
    #if defined _WIN32 || defined _WIN64
        LoadDynamicLibrary("Termi-GUI.dll", "tmain");
    #elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #endif

    return 0;
}
