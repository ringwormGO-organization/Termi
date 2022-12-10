#include <iostream>

#ifdef _WIN32
    
#elif _WIN64
    
#elif __APPLE__ || __MACH__
    #include <dlfcn.h>    
#elif __linux__
    #include <dlfcn.h>
#elif __FreeBSD__
    #include <dlfcn.h>
#endif

/* -------------------------- */

#ifdef _WIN32
    
#elif _WIN64
    
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
    
    #elif _WIN64
        
    #elif __APPLE__ || __MACH__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #elif __linux__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #elif __FreeBSD__
        LoadDynamicLibrary("libTermi-GUI.so", "tmain");
    #endif

    return 0;
}
