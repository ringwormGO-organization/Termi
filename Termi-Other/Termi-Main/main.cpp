#include <iostream>
#include <dlfcn.h>

void LoadSO(const char* function, int value)
{
    void *handle;
    void (*func)(int);
    char *error;

    handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        puts(" ");
        exit(1);
    }

    func = dlsym(handle, "tmain");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    (*func)(4); /* ignore this argument */
    dlclose(handle);
}

int main()
{
    LoadSO("test", 12);
    return 0;
}
