#include <iostream>

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
#elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
    __NetBSD__
    #include <dlfcn.h>
#endif

#if defined _WIN32 || defined _WIN64
    std::string GetLastErrorAsString()
    {
        DWORD errorMessageID = ::GetLastError();
        if (errorMessageID == 0) {
            return std::string();
        }

        LPSTR messageBuffer = nullptr;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

        std::string message(messageBuffer, size);
        LocalFree(messageBuffer);

        return message;
    }

    void LoadDynamicLibrary(const char* path, const char* function)
    {
        typedef int(__cdecl* FUNC)(int);

        HINSTANCE hinstLib;
        FUNC ProcAdd;
        BOOL fRunTimeLinkSuccess = FALSE;

        hinstLib = LoadLibrary(LPCSTR(path));

        if (hinstLib != NULL)
        {
            ProcAdd = (FUNC)GetProcAddress(hinstLib, function);

            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(12);
            }

            FreeLibrary(hinstLib);
        }

        if (!fRunTimeLinkSuccess)
        {
            printf("Failed to run function from executable!\n");
            printf("%d\n", GetLastError());
            std::cout << GetLastErrorAsString() << std::endl << std::endl;
        }
    }
#elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
    __NetBSD__
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

        (*func)(12);
        dlclose(handle);
    }
#endif

int main()
{
    #if defined _WIN32 || defined _WIN64
        LoadDynamicLibrary("Termi-GUI.dll", "tmain");
    #elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
        __NetBSD__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #endif

    return 0;
}

