#include <iostream>
#include <dlfcn.h>

void LoadSO(const char* path, const char* function)
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

int main()
{
    LoadSO("libTermi-GUI.so", "tmain");
    return 0;
}
