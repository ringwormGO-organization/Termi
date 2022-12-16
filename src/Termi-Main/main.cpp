#include <iostream>

#ifdef _WIN32
    #include <Windows.h>
#elif _WIN64
    #include <Windows.h>
#elif __APPLE__ || __MACH__
    #include <dlfcn.h>    
#elif __linux__
    #include <dlfcn.h>
#elif __FreeBSD__
    #include <dlfcn.h>
#endif

/* -------------------------- */

#ifdef _WIN32
    void LoadDynamicLibrary(const char* path, const char* function)
    {
        typedef int(__cdecl* FUNC)(int);

        HINSTANCE hinstLib;
        FUNC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.
        hinstLib = LoadLibrary(LPCSTR(path));

        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (FUNC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(12);
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Failed to run function from executable!\n");
        }
    }
#elif _WIN64
    void LoadDynamicLibrary(const char* path, const char* function)
    {
        typedef int(__cdecl* FUNC)(int);

        HINSTANCE hinstLib;
        FUNC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.
        hinstLib = LoadLibrary(LPCSTR(path));

        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (FUNC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(12);
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Failed to run function from executable!\n");
        }
    }
#elif __APPLE__ || __MACH__
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
#elif __linux__
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
#elif __FreeBSD__
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
    #ifdef _WIN32
        LoadDynamicLibrary("Termi-GUI.dll", "tmain");
    #elif _WIN64
        LoadDynamicLibrary("Termi-GUI.dll", "tmain");
    #elif __APPLE__ || __MACH__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #elif __linux__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #elif __FreeBSD__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #endif

    return 0;
}
