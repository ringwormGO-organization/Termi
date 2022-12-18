/**
 * @author Andrej Bartulin
 * PROJECT: Termi version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file for implementing core commands code
*/

#include "Export.h"

#include "Commands/base64.hpp"
#include "Commands/sysfetch.hpp"
#include "Commands/filesys.hpp"
#include "Commands/Geocalc.h"

#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <stdarg.h>

#ifdef _WIN32
    #include <Windows.h>
    #include <direct.h>
    #include <limits.h>
    #include "dirent.h"

    #include <lmcons.h>
    #include <tchar.h>
    #include <libloaderapi.h>
    #include <wchar.h>
    #include <intrin.h>

    #define _VOID void __cdecl
#elif _WIN64
    #include <Windows.h>
    #include <direct.h>
    #include <limits.h>
    #include "dirent.h"

    #include <lmcons.h>
    #include <tchar.h>
    #include <libloaderapi.h>
    #include <wchar.h>
    #include <intrin.h>

    #define _VOID void __cdecl
#elif __APPLE__ || __MACH__
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <limits.h>

    #include <dlfcn.h>
    #include <dirent.h>

    #define _VOID void
#elif __linux__
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <limits.h>

    #include <dlfcn.h>
    #include <dirent.h>

    #define _VOID void
#elif __FreeBSD__
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <limits.h>

    #include <dlfcn.h>
    #include <dirent.h>

    #define _VOID void __cdecl
#endif

using namespace std;

#ifdef _WIN32
    #pragma warning(disable: 4996)
    #pragma comment(lib, "Advapi32.lib")
    #pragma comment(lib, "Kernel32.lib")

    typedef int(__cdecl* MYPROC)(const char*);
    typedef void(__cdecl* RUST)(const char*);

    static void LoadDLL(const char* path, const char* function, const char* text, ...)
    {
        HINSTANCE hinstLib;
        MYPROC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.

        hinstLib = LoadLibrary(LPCSTR(path));

        // If the handle is valid, try to get the function address.

        if (hinstLib != NULL)
        {
            ProcAdd = (MYPROC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.

            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(text);
            }
            // Free the DLL module.

            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
            printf("Error!\n");

    }

    static int LoadRust(const char* path, const char* function, const char* value)
    {
        HINSTANCE hinstLib;
        RUST ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.

        hinstLib = LoadLibrary((LPCSTR)path);

        // If the handle is valid, try to get the function address.

        if (hinstLib != NULL)
        {
            ProcAdd = (RUST)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.

            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(value); /* ignore this number */
            }
            // Free the DLL module.

            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
            return 1;

        return 0;
    }

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadDLL("Termi-GUI.dll", "AddLog", buf);
    }

    /*
    * Commands main code
    * Return version of Windows operating system
    */
    static const char* OperatingSystem()
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

    /* Return uptime time in seoconds */
    uint64_t UptimeS()
    {
        return GetTickCount64() / 1000;
    }

    /* Return uptime time in minutes */
    uint64_t UptimeM()
    {
        return GetTickCount64() / 60000;
    }

    /* Return uptime time in hours */
    uint64_t UptimeH()
    {
        return GetTickCount64() / 3600000;
    }
#elif _WIN64
    #pragma warning(disable: 4996)
    #pragma comment(lib, "Advapi32.lib")
    #pragma comment(lib, "Kernel32.lib")

    typedef int(__cdecl* MYPROC)(const char*);
    typedef void(__cdecl* RUST)(const char*);

    static void LoadDLL(const char* path, const char* function, const char* text, ...)
    {
        HINSTANCE hinstLib;
        MYPROC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.

        hinstLib = LoadLibrary(LPCSTR(path));

        // If the handle is valid, try to get the function address.

        if (hinstLib != NULL)
        {
            ProcAdd = (MYPROC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.

            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(text);
            }
            // Free the DLL module.

            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
            printf("Error!\n");

    }

    static int LoadRust(const char* path, const char* function, const char* value)
    {
        HINSTANCE hinstLib;
        RUST ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.

        hinstLib = LoadLibrary((LPCSTR)path);

        // If the handle is valid, try to get the function address.

        if (hinstLib != NULL)
        {
            ProcAdd = (RUST)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.

            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(value); /* ignore this number */
            }
            // Free the DLL module.

            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
            return 1;

        return 0;
    }

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadDLL("Termi-GUI.dll", "AddLog", buf);
    }

    /*
    * Commands main code
    * Return version of Windows operating system
    */
    static const char* OperatingSystem()
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

    /* Return uptime time in seoconds */
    uint64_t UptimeS()
    {
        return GetTickCount64() / 1000;
    }

    /* Return uptime time in minutes */
    uint64_t UptimeM()
    {
        return GetTickCount64() / 60000;
    }

    /* Return uptime time in hours */
    uint64_t UptimeH()
    {
        return GetTickCount64() / 3600000;
    }
#elif __APPLE__ || __MACH__
    template <typename T>
    void LoadSO(const char* function, T value)
    {
        void *handle;
        void (*func)(T);
        char *error;

        handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(T)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(value); /* ignore this argument */
        dlclose(handle);
    }

    void LoadSO(int id, float value)
    {
        void *handle;
        void (*func)(int, float);
        char *error;

        handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(int, float)>(dlsym(handle, "tmain"));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(id, value);
        dlclose(handle);
    }

    int LoadRust(const char* path, const char* function, const char* value)
    {
        void *handle;
        void (*func)(const char*);
        char *error;

        handle = dlopen (path, RTLD_LAZY);
        if (!handle) {
            printf("%s\n", dlerror());
            printf("-------------\n");
            return 1;
        }

        func = reinterpret_cast<void (*)(const char*)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            printf("%s\n", error);
            printf("-------------\n");
            return 1;
        }

        (*func)(value);
        dlclose(handle);

        return 0;
    }

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadSO("AddLog", buf);
    }
#elif __linux__
    template <typename T>
    void LoadSO(const char* function, T value)
    {
        void *handle;
        void (*func)(T);
        char *error;

        handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(T)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(value); /* ignore this argument */
        dlclose(handle);
    }

    void LoadSO(int id, float value)
    {
        void *handle;
        void (*func)(int, float);
        char *error;

        handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(int, float)>(dlsym(handle, "tmain"));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(id, value);
        dlclose(handle);
    }

    int LoadRust(const char* path, const char* function, const char* value)
    {
        void *handle;
        void (*func)(const char*);
        char *error;

        handle = dlopen (path, RTLD_LAZY);
        if (!handle) {
            printf("%s\n", dlerror());
            printf("-------------\n");
            return 1;
        }

        func = reinterpret_cast<void (*)(const char*)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            printf("%s\n", error);
            printf("-------------\n");
            return 1;
        }

        (*func)(value);
        dlclose(handle);

        return 0;
    }

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadSO("AddLog", buf);
    }
#elif __FreeBSD__
    template <typename T>
    void LoadSO(const char* function, T value)
    {
        void *handle;
        void (*func)(T);
        char *error;

        handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(T)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(value); /* ignore this argument */
        dlclose(handle);
    }

    void LoadSO(int id, float value)
    {
        void *handle;
        void (*func)(int, float);
        char *error;

        handle = dlopen ("libTermi-GUI.so", RTLD_LAZY);
        if (!handle) {
            fputs (dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(int, float)>(dlsym(handle, "tmain"));
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(id, value);
        dlclose(handle);
    }

    int LoadRust(const char* path, const char* function, const char* value)
    {
        void *handle;
        void (*func)(const char*);
        char *error;

        handle = dlopen (path, RTLD_LAZY);
        if (!handle) {
            printf("%s\n", dlerror());
            printf("-------------\n");
            return 1;
        }

        func = reinterpret_cast<void (*)(const char*)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)  {
            printf("%s\n", error);
            printf("-------------\n");
            return 1;
        }

        (*func)(value);
        dlclose(handle);

        return 0;
    }

    void AddLog(std::string fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, sizeof(buf), fmt.c_str(), args);
        buf[sizeof(buf) - 1] = 0;
        va_end(args);

        LoadSO("AddLog", buf);
    }
#endif

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

/* ------------------------------------------------------------------------------------------ */

_VOID base64(const std::vector<std::string>& vect)
{
    if (vect.size() < 3)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    vector<string> out;

    if (vect[1] == "-e")
    {
        for (auto x : vect)
        {
            out.push_back(base64_encode(x));
        }

        vector<decltype(out)::value_type>(out.begin() + 2, out.end()).swap(out);

        AddLog("Result:\n");

        for (auto y : out)
        {
            AddLog(y);
        }

        Status(0);
    }

    else if (vect[1] == "-d")
    {
        for (auto x : vect)
        {
            out.push_back(base64_decode(x));
        }

        vector<decltype(out)::value_type>(out.begin() + 2, out.end()).swap(out);

        AddLog("Result:\n");

        for (auto y : out)
        {
            AddLog(y);
        }

        Status(0);
    }

    else
    {
        AddLog("Unknown parametar '%s'! Returning 1...\n", vect[1].c_str());
        Status(1);
        return;
    }
}

_VOID calc(const std::vector<std::string>& vect)
{
    if (vect.size() < 4)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    try
    {
        string op = vect[1];
        float num1 = stof(vect[2]);
        float num2 = stof(vect[3]);

        string result = "0";

        if (op == "+")
        {
            result = std::to_string(num1 + num2);
        }

        else if (op == "-")
        {
            result = std::to_string(num1 - num2);
        }

        else if (op == "*")
        {
            result = std::to_string(num1 * num2);
        }

        else if (op == "/")
        {
            if (num2 == 0)
            {
                AddLog("Cannot divide with 0!\n");
                Status(1);
                return;
            }

            else
            {
                result = std::to_string(num1 / num2);
            }
        }

        else
        {
            AddLog("Invalid operator '" + op + "'!\n");
            Status(1);
            return;
        }

        AddLog("Result is: " + result + "!\n");
        Status(0);
    }
    
    catch(const std::exception& e)
    {
        AddLog("Exception occured: ");
        AddLog(e.what());

        Status(2);
    }
}

_VOID cd(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    Status(chdir(vect[1].c_str()));
}

_VOID dencalc(const std::vector<std::string>& vect)
{
    if (vect.size() < 4)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    try
    {
        if (vect[1] != "x" && vect[2] != "x" && vect[3] == "x")
        {
            double result = stod(vect[1]) / stod(vect[2]);
            AddLog("Density of desired object is: %lf g/cm3", result);
            Status(0);
        }

        else if (vect[1] == "x" && vect[2] != "x" && vect[3] != "x")
        {
            double result = stod(vect[2]) * stod(vect[3]);
            AddLog("Mass of desired object is: %lf g", result);
            Status(0);
        }

        else if (vect[1] != "x" && vect[2] == "x" && vect[3] != "x")
        {
            double result = stod(vect[3]) * stod(vect[1]);
            AddLog("Volume of desired object is: %lf cm3", result);
            Status(0);
        }

        else
        {
            AddLog("Wrong arguments!\n");
            Status(1);
        }
    }

    catch(const std::exception& e)
    {
        AddLog("Exception occured: ");
        AddLog(e.what());

        Status(2);
    }
}

_VOID echo(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    if (vect[1].starts_with("$"))
    {
        AddLog("Variables not supported yet!\n");
        Status(1);
        return;
    }

    else
    {
        for (string x : vect)
        {
            AddLog(x.c_str());
        }
    }

    Status(0);
}

_VOID find_command(const std::vector<std::string>& vect)
{        
    #if __APPLE__ || __MACH__
        if (vect.size() < 5)
        {
            AddLog("Not enough arguments!");
            Status(1);
            return;
        }

        vector<string> out;

        out.push_back("list");
        out.push_back(vect[1]);
        out.push_back("!");

        list_dir(out);

        if (find(filesys.begin(), filesys.end(), vect[2]) != filesys.end())
        {
            AddLog("File/Directory '" + vect[2] + "' found.\n");
        }
        
        else
        {
            AddLog("File/Directory '" + vect[2] + "' not found!\n");

            out.clear();
            filesys.clear();

            Status(1);
            return;
        }

        out.clear();
        filesys.clear();

        Status(0);
    #elif __linux__
        if (vect.size() < 5)
        {
            AddLog("Not enough arguments!");
            Status(1);
            return;
        }

        vector<string> out;

        out.push_back("list");
        out.push_back(vect[1]);
        out.push_back("!");

        list_dir(out);

        if (find(filesys.begin(), filesys.end(), vect[2]) != filesys.end())
        {
            AddLog("File/Directory '" + vect[2] + "' found.\n");
        }
        
        else
        {
            AddLog("File/Directory '" + vect[2] + "' not found!\n");

            out.clear();
            filesys.clear();

            Status(1);
            return;
        }

        out.clear();
        filesys.clear();

        Status(0);
    #elif __FreeBSD__
        if (vect.size() < 5)
        {
            AddLog("Not enough arguments!");
            Status(1);
            return;
        }

        vector<string> out;

        out.push_back("list");
        out.push_back(vect[1]);
        out.push_back("!");

        list_dir(out);

        if (find(filesys.begin(), filesys.end(), vect[2]) != filesys.end())
        {
            AddLog("File/Directory '" + vect[2] + "' found.\n");
        }
        
        else
        {
            AddLog("File/Directory '" + vect[2] + "' not found!\n");

            out.clear();
            filesys.clear();

            Status(1);
            return;
        }

        out.clear();
        filesys.clear();

        Status(0);
    #endif

    Status(2);
}

_VOID geocalc(const std::vector<std::string>& vect)
{
    if (vect.size() < 5)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    string EXT = "EXT";
    string SUR = "SUR";
    string TRA = "TRA";
    string REC = "REC";
    string SQU = "SQU";

    string ext_or_sur = vect[1];

    try
    {
        if (ext_or_sur == SUR)
        {
            string TRA = "TRA";
            string REC = "REC";
            string SQU = "SQU";

            string rec_or_squ = vect[2];

            if (rec_or_squ == REC)
            {
                double x = stod(vect[3]);
                double y = stod(vect[4]);

                AddLog("Result: %f\n", povrsDvijustr(x, y));
            }

            else if (rec_or_squ == SQU)
            {
                double x = stod(vect[3]);

                AddLog("Result: %f\n", povrsKvdjustr(x));
            }

            else if (rec_or_squ == TRA)
            {
                double x = stod(vect[3]);
                double Vx = stod(vect[4]);

                AddLog("Result: %f\n", povrsTrokuta(x, Vx));
            }

            else
            {
                AddLog("Unknown input '%s'\n", rec_or_squ.c_str());
                Status(1);
                return;
            }
        }

        else if (ext_or_sur == EXT)
        {
            string TRA = "TRA";
            string REC = "REC";
            string SQU = "SQU";

            string tra_or_rec_or_squ = vect[1];

            if (tra_or_rec_or_squ == TRA)
            {
                double x = stod(vect[3]);
                double y = stod(vect[4]);
                double z = stod(vect[5]);

                AddLog("Result: %f\n", opsgTrijustr(x, y, z));
            }

            else if (tra_or_rec_or_squ == REC)
            {
                double x = stod(vect[3]);
                double y = stod(vect[4]);

                AddLog("Result: %f\n", opsgDvijustr(x, y));
            }

            else if (tra_or_rec_or_squ == SQU)
            {
                int sqe = 4;

                double x = stod(vect[3]);

                AddLog("Result: %f\n", opsgKvdjustr(x, sqe));
            }

            else
            {
                AddLog("Unknown input '%s'\n", tra_or_rec_or_squ.c_str());
                Status(1);
                return;
            }
        }

        else
        {
            AddLog("Unknown input '%s'\n", ext_or_sur.c_str());
            Status(1);
            return;
        }

        Status(0);
    }

    catch(const std::exception& e)
    {
        AddLog("Exception occured: ");
        AddLog(e.what());

        Status(2);
    }
}

_VOID list_dir(const std::vector<std::string>& vect)
{
    #ifdef _WIN32
        struct dirent* d;
        struct stat dst;

        DIR* dr;
        string path;

        if (vect.size() < 2)
        {
            path = ".\\";
        }

        else
        {
            path = vect[1];
        }

        _chdir(path.c_str());
        path = ".\\";

        dr = opendir(path.c_str());

        if (dr != NULL)
        {
            for (d = readdir(dr); d != NULL; d = readdir(dr))
            {
                string type = d->d_name;
                type = path + type;
                if (stat(type.c_str(), &dst) == 0)
                {
                    if (dst.st_mode & S_IFDIR)
                    {
                        type = "FOLDER";
                    }

                    else if (dst.st_mode & S_IFREG)
                    {
                        type = "FILE";
                    }
                }
                AddLog(d->d_name + type);
            }

            closedir(dr);
        }

        else
        {
            AddLog("Fatal error with directory!\n");
            Status(2);
        }
    #elif _WIN64
        struct dirent* d;
        struct stat dst;

        DIR* dr;
        string path;

        if (vect.size() < 2)
        {
            path = ".\\";
        }

        else
        {
            path = vect[1];
        }

        _chdir(path.c_str());
        path = ".\\";

        dr = opendir(path.c_str());

        if (dr != NULL)
        {
            for (d = readdir(dr); d != NULL; d = readdir(dr))
            {
                string type = d->d_name;
                type = path + type;
                if (stat(type.c_str(), &dst) == 0)
                {
                    if (dst.st_mode & S_IFDIR)
                    {
                        type = "FOLDER";
                    }

                    else if (dst.st_mode & S_IFREG)
                    {
                        type = "FILE";
                    }
                }
                AddLog(d->d_name + type);
            }

            closedir(dr);
        }

        else
        {
            AddLog("Fatal error with directory!\n");
            Status(2);
        }
    #elif __APPLE__ || __MACH__
        if (vect[1] != "")
        {
            chdir(vect[1].c_str());
        }

        DIR *dr;
        struct dirent *en;
        dr = opendir("."); /* open all directory */

        if (dr) 
        {
            while ((en = readdir(dr)) != NULL) 
            {
                filesys.push_back(en->d_name);
            }

            closedir(dr); /* close all directory */
            sort(filesys.begin(), filesys.end());

            for (auto x : filesys)
            {
                AddLog(x + "\n");
            }

            AddLog("Total: " + std::to_string(filesys.size()) + "\n");

            if (vect[2] == "")
            {
                filesys.clear();
            }
        }

        else
        {
            Status(2);
        }
    #elif __linux__
        if (vect[1] != "")
        {
            chdir(vect[1].c_str());
        }

        DIR *dr;
        struct dirent *en;
        dr = opendir("."); /* open all directory */

        if (dr) 
        {
            while ((en = readdir(dr)) != NULL) 
            {
                filesys.push_back(en->d_name);
            }

            closedir(dr); /* close all directory */
            sort(filesys.begin(), filesys.end());

            for (auto x : filesys)
            {
                AddLog(x + "\n");
            }

            AddLog("Total: " + std::to_string(filesys.size()) + "\n");

            if (vect[2] == "")
            {
                filesys.clear();
            }
        }

        else
        {
            Status(2);
        }
    #elif __FreeBSD__
        if (vect[1] != "")
        {
            chdir(vect[1].c_str());
        }

        DIR *dr;
        struct dirent *en;
        dr = opendir("."); /* open all directory */

        if (dr) 
        {
            while ((en = readdir(dr)) != NULL) 
            {
                filesys.push_back(en->d_name);
            }

            closedir(dr); /* close all directory */
            sort(filesys.begin(), filesys.end());

            for (auto x : filesys)
            {
                AddLog(x + "\n");
            }

            AddLog("Total: " + std::to_string(filesys.size()) + "\n");

            if (vect[2] == "")
            {
                filesys.clear();
            }
        }

        else
        {
            Status(2);
        }
    #endif


    Status(0);
}

_VOID new_dir(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    #ifdef _WIN32
        if (mkdir(vect[1].c_str()) == -1)
        {
            AddLog("Error while creating directory!\n");
            Status(2);
            return;
        }

        else
        {
            AddLog("Directory '" + vect[1] + "' created!\n");
            Status(0);
        }
    #elif _WIN64
        if (mkdir(vect[1].c_str()) == -1)
        {
            AddLog("Error while creating directory!\n");
            Status(2);
            return;
        }

        else
        {
            AddLog("Directory '" + vect[1] + "' created!\n");
            Status(0);
        }
    #elif __APPLE__ || __MACH__
        if (mkdir(vect[1].c_str(), 0777) == -1)
        {
            AddLog("Error while creating directory!\n");
            Status(2);
            return;
        }

        else
        {
            AddLog("Directory '" + vect[1] + "' created!\n");
            Status(0);
        }
    #elif __linux__
        if (mkdir(vect[1].c_str(), 0777) == -1)
        {
            AddLog("Error while creating directory!\n");
            Status(2);
            return;
        }

        else
        {
            AddLog("Directory '" + vect[1] + "' created!\n");
            Status(0);
        }
    #elif __FreeBSD__
        if (mkdir(vect[1].c_str(), 0777) == -1)
        {
            AddLog("Error while creating directory!\n");
            Status(2);
            return;
        }

        else
        {
            AddLog("Directory '" + vect[1] + "' created!\n");
            Status(0);
        }
    #endif
}

_VOID sysfetch(const std::vector<std::string>& vect)
{
    /* Username and computer name */
    #ifdef _WIN32
        TCHAR username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName((TCHAR*)username, &username_len);

        TCHAR computer[UNLEN + 1];
        DWORD computer_len = UNLEN + 1;
        GetComputerName((TCHAR*)computer, &computer_len);

        char new_username[UNLEN];
        char new_computer[UNLEN];

        /*wcstombs(new_username, username, wcslen(username) + 1);
        wcstombs(new_computer, computer, wcslen(computer) + 1);*/

        strcpy_s(new_username, UNLEN, username);
        strcpy_s(new_computer, UNLEN, computer);
    #elif _WIN64
        TCHAR username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName((TCHAR*)username, &username_len);

        TCHAR computer[UNLEN + 1];
        DWORD computer_len = UNLEN + 1;
        GetComputerName((TCHAR*)computer, &computer_len);

        char new_username[UNLEN];
        char new_computer[UNLEN];

        wcstombs(new_username, username, wcslen(username) + 1);
        wcstombs(new_computer, computer, wcslen(computer) + 1);
    #elif __APPLE__ || __MACH__
        gethostname(info.computer, 256);
        getlogin_r(info.user, 64);
    #elif __linux__
        gethostname(info.computer, 256);
        getlogin_r(info.user, 64);
    #elif __FreeBSD__
        gethostname(info.computer, 256);
        getlogin_r(info.user, 64);
    #endif

    /* OS */
    #ifdef _WIN32
        /* info.OS = "Windows32"; */
    #elif _WIN64
        /* info.OS = "Windows64"; */
    #elif __APPLE__ || __MACH__
        /* info.OS = "Mac OSX"; */
    #elif __linux__
        info.OS = "(GNU/)Linux";
    #elif __FreeBSD__
        /* info.OS = "FreeBSD"; */
    #elif __unix || __unix__
        /* info.OS = "Unix"; */
    #else
        /* info.OS = "Other"; */
    #endif

    /* CPU */
    #ifdef __linux__
        string cpu;
        string line_pre_array = parse("model name", "/proc/cpuinfo");
        vector<string> result = explode(line_pre_array, ':');
        cpu = result[1];
        cpu = regex_replace(cpu, regex("^ +"), "");
        info.cpu = cpu;
    #endif

    /* Memory */
    #ifdef _WIN32
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
    #elif _WIN64
        MEMORYSTATUSEX statex;
        statex.dwLength = sizeof(statex);
        GlobalMemoryStatusEx(&statex);
    #elif __linux__
        string total_line = parse("MemTotal", "/proc/meminfo");
        vector<string> total_line_vector = explode(total_line, ' ');
        int total_size = stoi(total_line_vector[1]);
        if (total_size > 1024) 
        {
            int total = total_size / 1024;
            string message_total = to_string(total);
            string message = message_total + "MB";
            info.memory = message;
        }

        else 
        {
            string message_total = to_string(total_size);
            string message = message_total + "KB";
            info.memory = message;
        }
    #endif

    /* Uptime */
    #ifdef _WIN32
        
    #elif _WIN64

    #elif __linux__
        chrono::milliseconds uptime(0u);
        double uptime_seconds;
        if (ifstream("/proc/uptime", ios::in) >> uptime_seconds)
        {
            uptime = chrono::milliseconds
            (
                static_cast<unsigned long long>(uptime_seconds * 1000.0)
            );
        }

        else
        {
            Status(2);
            return;
        }

    info.uptime = uptime_seconds / 3600;
    #endif

    #ifdef _WIN32
        AddLog("\n");
        AddLog("\t " + string(new_username) + " @ " + string(new_computer) + "\n");
        AddLog("-------------------------------------------- \n");

        AddLog("\n");
        AddLog("\tOperating system: " + string(OperatingSystem()) + "\n");

        if (UptimeH() < 1)
        {
            AddLog("\t Uptime: " + std::to_string(UptimeM()) + " minutes\n");
        }

        else
        {
            AddLog("\t Uptime: " + std::to_string(UptimeH()) + " hours\n");
        }
    #elif _WIN64
        AddLog("\n");
        AddLog("\t " + string(new_username) + " @ " + string(new_computer) + "\n");
        AddLog("-------------------------------------------- \n");

        AddLog("\n");
        AddLog("\tOperating system: " + string(OperatingSystem()) + "\n");

        if (UptimeH() < 1)
        {
            AddLog("\t Uptime: " + std::to_string(UptimeM()) + " minutes\n");
        }

        else
        {
            AddLog("\t Uptime: " + std::to_string(UptimeH()) + " hours\n");
        }
    #elif __APPLE__ || __MACH__
        AddLog("\n");
        AddLog("\t " + string(info.user) + " @ " + string(info.computer) + "\n");
        AddLog("--------------------------------------------\n");

        AddLog("\n");
        AddLog("\tOperating system: " + info.OS + ", " + distro() + "\n");
        AddLog("\tUptime: " + std::to_string(info.uptime) + " hours\n");
        AddLog("\tPackages: " + packages() + "\n");

        AddLog("\tCPU: " + info.cpu + "\n");
        AddLog("\tMemory: " + info.memory + "\n");
        AddLog("\n");
    #elif __linux__
        AddLog("\n");
        AddLog("\t " + string(info.user) + " @ " + string(info.computer) + "\n");
        AddLog("--------------------------------------------\n");

        AddLog("\n");
        AddLog("\tOperating system: " + info.OS + ", " + distro() + "\n");
        AddLog("\tUptime: " + std::to_string(info.uptime) + " hours\n");
        AddLog("\tPackages: " + packages() + "\n");

        AddLog("\tCPU: " + info.cpu + "\n");
        AddLog("\tMemory: " + info.memory + "\n");
        AddLog("\n");
    #elif __FreeBSD__
        AddLog("\n");
        AddLog("\t " + string(info.user) + " @ " + string(info.computer) + "\n");
        AddLog("--------------------------------------------\n");

        AddLog("\n");
        AddLog("\tOperating system: " + info.OS + ", " + distro() + "\n");
        AddLog("\tUptime: " + std::to_string(info.uptime) + " hours\n");
        AddLog("\tPackages: " + packages() + "\n");

        AddLog("\tCPU: " + info.cpu + "\n");
        AddLog("\tMemory: " + info.memory + "\n");
        AddLog("\n");
    #endif

    #ifdef _WIN32
        int regs[4] = { 0 };
        char vendor[13];
        __cpuid(regs, 0);              // mov eax,0; cpuid
        memcpy(vendor, &regs[1], 4);   // copy EBX
        memcpy(vendor + 4, &regs[3], 4); // copy EDX
        memcpy(vendor + 8, &regs[2], 4); // copy ECX
        vendor[12] = '\0';

        AddLog("\t--------------------- CPU --------------------\t\n");

        char CPUString[0x20];
        char CPUBrandString[0x40];
        int CPUInfo[4] = { -1 };
        int nSteppingID = 0;
        int nModel = 0;
        int nFamily = 0;
        int nProcessorType = 0;
        int nExtendedmodel = 0;
        int nExtendedfamily = 0;
        int nBrandIndex = 0;
        int nCLFLUSHcachelinesize = 0;
        int nLogicalProcessors = 0;
        int nAPICPhysicalID = 0;
        int nFeatureInfo = 0;
        int nCacheLineSize = 0;
        int nL2Associativity = 0;
        int nCacheSizeK = 0;
        int nPhysicalAddress = 0;
        int nVirtualAddress = 0;
        int nRet = 0;

        int nCores = 0;
        int nCacheType = 0;
        int nCacheLevel = 0;
        int nMaxThread = 0;
        int nSysLineSize = 0;
        int nPhysicalLinePartitions = 0;
        int nWaysAssociativity = 0;
        int nNumberSets = 0;

        unsigned    nIds, nExIds, i;

        bool    bSSE3Instructions = false;
        bool    bMONITOR_MWAIT = false;
        bool    bCPLQualifiedDebugStore = false;
        bool    bVirtualMachineExtensions = false;
        bool    bEnhancedIntelSpeedStepTechnology = false;
        bool    bThermalMonitor2 = false;
        bool    bSupplementalSSE3 = false;
        bool    bL1ContextID = false;
        bool    bCMPXCHG16B = false;
        bool    bxTPRUpdateControl = false;
        bool    bPerfDebugCapabilityMSR = false;
        bool    bSSE41Extensions = false;
        bool    bSSE42Extensions = false;
        bool    bPOPCNT = false;

        bool    bMultithreading = false;

        bool    bLAHF_SAHFAvailable = false;
        bool    bCmpLegacy = false;
        bool    bSVM = false;
        bool    bExtApicSpace = false;
        bool    bAltMovCr8 = false;
        bool    bLZCNT = false;
        bool    bSSE4A = false;
        bool    bMisalignedSSE = false;
        bool    bPREFETCH = false;
        bool    bSKINITandDEV = false;
        bool    bSYSCALL_SYSRETAvailable = false;
        bool    bExecuteDisableBitAvailable = false;
        bool    bMMXExtensions = false;
        bool    bFFXSR = false;
        bool    b1GBSupport = false;
        bool    bRDTSCP = false;
        bool    b64Available = false;
        bool    b3DNowExt = false;
        bool    b3DNow = false;
        bool    bNestedPaging = false;
        bool    bLBRVisualization = false;
        bool    bFP128 = false;
        bool    bMOVOptimization = false;

        bool    bSelfInit = false;
        bool    bFullyAssociative = false;


        // __cpuid with an InfoType argument of 0 returns the number of
        // valid Ids in CPUInfo[0] and the CPU identification string in
        // the other three array elements. The CPU identification string is
        // not in linear order. The code below arranges the information 
        // in a human readable form.
        __cpuid(CPUInfo, 0);
        nIds = CPUInfo[0];
        memset(CPUString, 0, sizeof(CPUString));
        *((int*)CPUString) = CPUInfo[1];
        *((int*)(CPUString + 4)) = CPUInfo[3];
        *((int*)(CPUString + 8)) = CPUInfo[2];

        // Get the information associated with each valid Id
        for (i = 0; i <= nIds; ++i)
        {
            __cpuid(CPUInfo, i);

            // Interpret CPU feature information.
            if (i == 1)
            {
                nSteppingID = CPUInfo[0] & 0xf;
                nModel = (CPUInfo[0] >> 4) & 0xf;
                nFamily = (CPUInfo[0] >> 8) & 0xf;
                nProcessorType = (CPUInfo[0] >> 12) & 0x3;
                nExtendedmodel = (CPUInfo[0] >> 16) & 0xf;
                nExtendedfamily = (CPUInfo[0] >> 20) & 0xff;
                nBrandIndex = CPUInfo[1] & 0xff;
                nCLFLUSHcachelinesize = ((CPUInfo[1] >> 8) & 0xff) * 8;
                nLogicalProcessors = ((CPUInfo[1] >> 16) & 0xff);
                nAPICPhysicalID = (CPUInfo[1] >> 24) & 0xff;
                bSSE3Instructions = (CPUInfo[2] & 0x1) || false;
                bMONITOR_MWAIT = (CPUInfo[2] & 0x8) || false;
                bCPLQualifiedDebugStore = (CPUInfo[2] & 0x10) || false;
                bVirtualMachineExtensions = (CPUInfo[2] & 0x20) || false;
                bEnhancedIntelSpeedStepTechnology = (CPUInfo[2] & 0x80) || false;
                bThermalMonitor2 = (CPUInfo[2] & 0x100) || false;
                bSupplementalSSE3 = (CPUInfo[2] & 0x200) || false;
                bL1ContextID = (CPUInfo[2] & 0x300) || false;
                bCMPXCHG16B = (CPUInfo[2] & 0x2000) || false;
                bxTPRUpdateControl = (CPUInfo[2] & 0x4000) || false;
                bPerfDebugCapabilityMSR = (CPUInfo[2] & 0x8000) || false;
                bSSE41Extensions = (CPUInfo[2] & 0x80000) || false;
                bSSE42Extensions = (CPUInfo[2] & 0x100000) || false;
                bPOPCNT = (CPUInfo[2] & 0x800000) || false;
                nFeatureInfo = CPUInfo[3];
                bMultithreading = (nFeatureInfo & (1 << 28)) || false;
            }
        }

        // Calling __cpuid with 0x80000000 as the InfoType argument
        // gets the number of valid extended IDs.
        __cpuid(CPUInfo, 0x80000000);
        nExIds = CPUInfo[0];
        memset(CPUBrandString, 0, sizeof(CPUBrandString));

        // Get the information associated with each extended ID.
        for (i = 0x80000000; i <= nExIds; ++i)
        {
            __cpuid(CPUInfo, i);

            if (i == 0x80000001)
            {
                bLAHF_SAHFAvailable = (CPUInfo[2] & 0x1) || false;
                bCmpLegacy = (CPUInfo[2] & 0x2) || false;
                bSVM = (CPUInfo[2] & 0x4) || false;
                bExtApicSpace = (CPUInfo[2] & 0x8) || false;
                bAltMovCr8 = (CPUInfo[2] & 0x10) || false;
                bLZCNT = (CPUInfo[2] & 0x20) || false;
                bSSE4A = (CPUInfo[2] & 0x40) || false;
                bMisalignedSSE = (CPUInfo[2] & 0x80) || false;
                bPREFETCH = (CPUInfo[2] & 0x100) || false;
                bSKINITandDEV = (CPUInfo[2] & 0x1000) || false;
                bSYSCALL_SYSRETAvailable = (CPUInfo[3] & 0x800) || false;
                bExecuteDisableBitAvailable = (CPUInfo[3] & 0x10000) || false;
                bMMXExtensions = (CPUInfo[3] & 0x40000) || false;
                bFFXSR = (CPUInfo[3] & 0x200000) || false;
                b1GBSupport = (CPUInfo[3] & 0x400000) || false;
                bRDTSCP = (CPUInfo[3] & 0x8000000) || false;
                b64Available = (CPUInfo[3] & 0x20000000) || false;
                b3DNowExt = (CPUInfo[3] & 0x40000000) || false;
                b3DNow = (CPUInfo[3] & 0x80000000) || false;
            }

            // Interpret CPU brand string and cache information.
            if (i == 0x80000002)
                memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000003)
                memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000004)
                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000006)
            {
                nCacheLineSize = CPUInfo[2] & 0xff;
                nL2Associativity = (CPUInfo[2] >> 12) & 0xf;
                nCacheSizeK = (CPUInfo[2] >> 16) & 0xffff;
            }
            else if (i == 0x80000008)
            {
                nPhysicalAddress = CPUInfo[0] & 0xff;
                nVirtualAddress = (CPUInfo[0] >> 8) & 0xff;
            }
            else if (i == 0x8000000A)
            {
                bNestedPaging = (CPUInfo[3] & 0x1) || false;
                bLBRVisualization = (CPUInfo[3] & 0x2) || false;
            }
            else if (i == 0x8000001A)
            {
                bFP128 = (CPUInfo[0] & 0x1) || false;
                bMOVOptimization = (CPUInfo[0] & 0x2) || false;
            }
        }

        // Display all the information in user-friendly format.
        AddLog("\tCPU String: " + string(CPUString) + "\n");

        if (nIds >= 1)
        {
            if (nSteppingID)
                AddLog("\tStepping ID = %d\t\n", nSteppingID);
            if (nModel)
                AddLog("\tModel = %d\t\n", nModel);
            if (nFamily)
                AddLog("\tFamily = %d\t\n", nFamily);
            if (nProcessorType)
                AddLog("\tProcessor Type = %d\t\n", nProcessorType);
            if (nExtendedmodel)
                AddLog("\tExtended model = %d\t\n", nExtendedmodel);
            if (nExtendedfamily)
                AddLog("\tExtended family = %d\t\n", nExtendedfamily);
            if (nBrandIndex)
                AddLog("\tBrand Index = %d\t\n", nBrandIndex);
            if (nCLFLUSHcachelinesize)
                AddLog("\tCLFLUSH cache line size = %d\t\n",
                    nCLFLUSHcachelinesize);
            if (bMultithreading && (nLogicalProcessors > 0))
                AddLog("\tLogical Processor Count = %d\t\n", nLogicalProcessors);
            if (nAPICPhysicalID)
                AddLog("\tAPIC Physical ID = %d\t\n", nAPICPhysicalID);
        }

        AddLog("\n");

        if (nExIds >= 0x80000004)
            AddLog("\tCPU Brand String: %s\t\n", CPUBrandString);

        if (nExIds >= 0x80000006)
        {
            AddLog("\tCache Line Size = %d\t\n", nCacheLineSize);
            AddLog("\tL2 Associativity = %d\t\n", nL2Associativity);
            AddLog("\tCache Size = %dK\t\n", nCacheSizeK);
        }


        for (i = 0;; i++)
        {
            __cpuidex(CPUInfo, 0x4, i);
            if (!(CPUInfo[0] & 0xf0)) break;

            if (i == 0)
            {
                nCores = CPUInfo[0] >> 26;
                AddLog("\tNumber of Cores = %d\t\n", nCores + 1);
            }

            nCacheType = (CPUInfo[0] & 0x1f);
            nCacheLevel = (CPUInfo[0] & 0xe0) >> 5;
            bSelfInit = (CPUInfo[0] & 0x100) >> 8;
            bFullyAssociative = (CPUInfo[0] & 0x200) >> 9;
            nMaxThread = (CPUInfo[0] & 0x03ffc000) >> 14;
            nSysLineSize = (CPUInfo[1] & 0x0fff);
            nPhysicalLinePartitions = (CPUInfo[1] & 0x03ff000) >> 12;
            nWaysAssociativity = (CPUInfo[1]) >> 22;
            nNumberSets = CPUInfo[2];

            AddLog("\n");

            AddLog("\tECX Index %d\t\n", i);
            switch (nCacheType)
            {
            case 0:
                AddLog("\t   Type: Null\t\n");
                break;
            case 1:
                AddLog("\t   Type: Data Cache\t\n");
                break;
            case 2:
                AddLog("\t   Type: Instruction Cache\t\n");
                break;
            case 3:
                AddLog("\t   Type: Unified Cache\t\n");
                break;
            default:
                AddLog("\t   Type: Unknown\t\n");
            }

            AddLog("\t   Level = %d\t\n", nCacheLevel + 1);
            if (bSelfInit)
            {
                AddLog("\t   Self Initializing\t\n");
            }
            else
            {
                AddLog("\t   Not Self Initializing\t\n");
            }
            if (bFullyAssociative)
            {
                AddLog("\t   Is Fully Associatve\t\n");
            }
            else
            {
                AddLog("\t   Is Not Fully Associatve\t\n");
            }
            AddLog("\t   Max Threads = %d\t\n",
                nMaxThread + 1);
            AddLog("\t   System Line Size = %d\t\n",
                nSysLineSize + 1);
            AddLog("\t   Physical Line Partions = %d\t\n",
                nPhysicalLinePartitions + 1);
            AddLog("\t   Ways of Associativity = %d\t\n",
                nWaysAssociativity + 1);
            AddLog("\t   Number of Sets = %d\t\n",
                nNumberSets + 1);
        }

        AddLog("\t--------------------- CPU --------------------\t\n");

        float physf = (float)statex.ullTotalPhys / (1024 * 1024 * 1024);
        string phys = std::to_string(physf);

        AddLog("\tMemory: " + phys + " GB\n\n");
    #elif _WIN64
        int regs[4] = { 0 };
        char vendor[13];
        __cpuid(regs, 0);              // mov eax,0; cpuid
        memcpy(vendor, &regs[1], 4);   // copy EBX
        memcpy(vendor + 4, &regs[3], 4); // copy EDX
        memcpy(vendor + 8, &regs[2], 4); // copy ECX
        vendor[12] = '\0';

        AddLog("\t--------------------- CPU --------------------\t\n");

        char CPUString[0x20];
        char CPUBrandString[0x40];
        int CPUInfo[4] = { -1 };
        int nSteppingID = 0;
        int nModel = 0;
        int nFamily = 0;
        int nProcessorType = 0;
        int nExtendedmodel = 0;
        int nExtendedfamily = 0;
        int nBrandIndex = 0;
        int nCLFLUSHcachelinesize = 0;
        int nLogicalProcessors = 0;
        int nAPICPhysicalID = 0;
        int nFeatureInfo = 0;
        int nCacheLineSize = 0;
        int nL2Associativity = 0;
        int nCacheSizeK = 0;
        int nPhysicalAddress = 0;
        int nVirtualAddress = 0;
        int nRet = 0;

        int nCores = 0;
        int nCacheType = 0;
        int nCacheLevel = 0;
        int nMaxThread = 0;
        int nSysLineSize = 0;
        int nPhysicalLinePartitions = 0;
        int nWaysAssociativity = 0;
        int nNumberSets = 0;

        unsigned    nIds, nExIds, i;

        bool    bSSE3Instructions = false;
        bool    bMONITOR_MWAIT = false;
        bool    bCPLQualifiedDebugStore = false;
        bool    bVirtualMachineExtensions = false;
        bool    bEnhancedIntelSpeedStepTechnology = false;
        bool    bThermalMonitor2 = false;
        bool    bSupplementalSSE3 = false;
        bool    bL1ContextID = false;
        bool    bCMPXCHG16B = false;
        bool    bxTPRUpdateControl = false;
        bool    bPerfDebugCapabilityMSR = false;
        bool    bSSE41Extensions = false;
        bool    bSSE42Extensions = false;
        bool    bPOPCNT = false;

        bool    bMultithreading = false;

        bool    bLAHF_SAHFAvailable = false;
        bool    bCmpLegacy = false;
        bool    bSVM = false;
        bool    bExtApicSpace = false;
        bool    bAltMovCr8 = false;
        bool    bLZCNT = false;
        bool    bSSE4A = false;
        bool    bMisalignedSSE = false;
        bool    bPREFETCH = false;
        bool    bSKINITandDEV = false;
        bool    bSYSCALL_SYSRETAvailable = false;
        bool    bExecuteDisableBitAvailable = false;
        bool    bMMXExtensions = false;
        bool    bFFXSR = false;
        bool    b1GBSupport = false;
        bool    bRDTSCP = false;
        bool    b64Available = false;
        bool    b3DNowExt = false;
        bool    b3DNow = false;
        bool    bNestedPaging = false;
        bool    bLBRVisualization = false;
        bool    bFP128 = false;
        bool    bMOVOptimization = false;

        bool    bSelfInit = false;
        bool    bFullyAssociative = false;


        // __cpuid with an InfoType argument of 0 returns the number of
        // valid Ids in CPUInfo[0] and the CPU identification string in
        // the other three array elements. The CPU identification string is
        // not in linear order. The code below arranges the information 
        // in a human readable form.
        __cpuid(CPUInfo, 0);
        nIds = CPUInfo[0];
        memset(CPUString, 0, sizeof(CPUString));
        *((int*)CPUString) = CPUInfo[1];
        *((int*)(CPUString + 4)) = CPUInfo[3];
        *((int*)(CPUString + 8)) = CPUInfo[2];

        // Get the information associated with each valid Id
        for (i = 0; i <= nIds; ++i)
        {
            __cpuid(CPUInfo, i);

            // Interpret CPU feature information.
            if (i == 1)
            {
                nSteppingID = CPUInfo[0] & 0xf;
                nModel = (CPUInfo[0] >> 4) & 0xf;
                nFamily = (CPUInfo[0] >> 8) & 0xf;
                nProcessorType = (CPUInfo[0] >> 12) & 0x3;
                nExtendedmodel = (CPUInfo[0] >> 16) & 0xf;
                nExtendedfamily = (CPUInfo[0] >> 20) & 0xff;
                nBrandIndex = CPUInfo[1] & 0xff;
                nCLFLUSHcachelinesize = ((CPUInfo[1] >> 8) & 0xff) * 8;
                nLogicalProcessors = ((CPUInfo[1] >> 16) & 0xff);
                nAPICPhysicalID = (CPUInfo[1] >> 24) & 0xff;
                bSSE3Instructions = (CPUInfo[2] & 0x1) || false;
                bMONITOR_MWAIT = (CPUInfo[2] & 0x8) || false;
                bCPLQualifiedDebugStore = (CPUInfo[2] & 0x10) || false;
                bVirtualMachineExtensions = (CPUInfo[2] & 0x20) || false;
                bEnhancedIntelSpeedStepTechnology = (CPUInfo[2] & 0x80) || false;
                bThermalMonitor2 = (CPUInfo[2] & 0x100) || false;
                bSupplementalSSE3 = (CPUInfo[2] & 0x200) || false;
                bL1ContextID = (CPUInfo[2] & 0x300) || false;
                bCMPXCHG16B = (CPUInfo[2] & 0x2000) || false;
                bxTPRUpdateControl = (CPUInfo[2] & 0x4000) || false;
                bPerfDebugCapabilityMSR = (CPUInfo[2] & 0x8000) || false;
                bSSE41Extensions = (CPUInfo[2] & 0x80000) || false;
                bSSE42Extensions = (CPUInfo[2] & 0x100000) || false;
                bPOPCNT = (CPUInfo[2] & 0x800000) || false;
                nFeatureInfo = CPUInfo[3];
                bMultithreading = (nFeatureInfo & (1 << 28)) || false;
            }
        }

        // Calling __cpuid with 0x80000000 as the InfoType argument
        // gets the number of valid extended IDs.
        __cpuid(CPUInfo, 0x80000000);
        nExIds = CPUInfo[0];
        memset(CPUBrandString, 0, sizeof(CPUBrandString));

        // Get the information associated with each extended ID.
        for (i = 0x80000000; i <= nExIds; ++i)
        {
            __cpuid(CPUInfo, i);

            if (i == 0x80000001)
            {
                bLAHF_SAHFAvailable = (CPUInfo[2] & 0x1) || false;
                bCmpLegacy = (CPUInfo[2] & 0x2) || false;
                bSVM = (CPUInfo[2] & 0x4) || false;
                bExtApicSpace = (CPUInfo[2] & 0x8) || false;
                bAltMovCr8 = (CPUInfo[2] & 0x10) || false;
                bLZCNT = (CPUInfo[2] & 0x20) || false;
                bSSE4A = (CPUInfo[2] & 0x40) || false;
                bMisalignedSSE = (CPUInfo[2] & 0x80) || false;
                bPREFETCH = (CPUInfo[2] & 0x100) || false;
                bSKINITandDEV = (CPUInfo[2] & 0x1000) || false;
                bSYSCALL_SYSRETAvailable = (CPUInfo[3] & 0x800) || false;
                bExecuteDisableBitAvailable = (CPUInfo[3] & 0x10000) || false;
                bMMXExtensions = (CPUInfo[3] & 0x40000) || false;
                bFFXSR = (CPUInfo[3] & 0x200000) || false;
                b1GBSupport = (CPUInfo[3] & 0x400000) || false;
                bRDTSCP = (CPUInfo[3] & 0x8000000) || false;
                b64Available = (CPUInfo[3] & 0x20000000) || false;
                b3DNowExt = (CPUInfo[3] & 0x40000000) || false;
                b3DNow = (CPUInfo[3] & 0x80000000) || false;
            }

            // Interpret CPU brand string and cache information.
            if (i == 0x80000002)
                memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000003)
                memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000004)
                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
            else if (i == 0x80000006)
            {
                nCacheLineSize = CPUInfo[2] & 0xff;
                nL2Associativity = (CPUInfo[2] >> 12) & 0xf;
                nCacheSizeK = (CPUInfo[2] >> 16) & 0xffff;
            }
            else if (i == 0x80000008)
            {
                nPhysicalAddress = CPUInfo[0] & 0xff;
                nVirtualAddress = (CPUInfo[0] >> 8) & 0xff;
            }
            else if (i == 0x8000000A)
            {
                bNestedPaging = (CPUInfo[3] & 0x1) || false;
                bLBRVisualization = (CPUInfo[3] & 0x2) || false;
            }
            else if (i == 0x8000001A)
            {
                bFP128 = (CPUInfo[0] & 0x1) || false;
                bMOVOptimization = (CPUInfo[0] & 0x2) || false;
            }
        }

        // Display all the information in user-friendly format.
        AddLog("\tCPU String: " + string(CPUString) + "\n");

        if (nIds >= 1)
        {
            if (nSteppingID)
                AddLog("\tStepping ID = %d\t\n", nSteppingID);
            if (nModel)
                AddLog("\tModel = %d\t\n", nModel);
            if (nFamily)
                AddLog("\tFamily = %d\t\n", nFamily);
            if (nProcessorType)
                AddLog("\tProcessor Type = %d\t\n", nProcessorType);
            if (nExtendedmodel)
                AddLog("\tExtended model = %d\t\n", nExtendedmodel);
            if (nExtendedfamily)
                AddLog("\tExtended family = %d\t\n", nExtendedfamily);
            if (nBrandIndex)
                AddLog("\tBrand Index = %d\t\n", nBrandIndex);
            if (nCLFLUSHcachelinesize)
                AddLog("\tCLFLUSH cache line size = %d\t\n",
                    nCLFLUSHcachelinesize);
            if (bMultithreading && (nLogicalProcessors > 0))
                AddLog("\tLogical Processor Count = %d\t\n", nLogicalProcessors);
            if (nAPICPhysicalID)
                AddLog("\tAPIC Physical ID = %d\t\n", nAPICPhysicalID);
        }

        AddLog("\n");

        if (nExIds >= 0x80000004)
            AddLog("\tCPU Brand String: %s\t\n", CPUBrandString);

        if (nExIds >= 0x80000006)
        {
            AddLog("\tCache Line Size = %d\t\n", nCacheLineSize);
            AddLog("\tL2 Associativity = %d\t\n", nL2Associativity);
            AddLog("\tCache Size = %dK\t\n", nCacheSizeK);
        }


        for (i = 0;; i++)
        {
            __cpuidex(CPUInfo, 0x4, i);
            if (!(CPUInfo[0] & 0xf0)) break;

            if (i == 0)
            {
                nCores = CPUInfo[0] >> 26;
                AddLog("\tNumber of Cores = %d\t\n", nCores + 1);
            }

            nCacheType = (CPUInfo[0] & 0x1f);
            nCacheLevel = (CPUInfo[0] & 0xe0) >> 5;
            bSelfInit = (CPUInfo[0] & 0x100) >> 8;
            bFullyAssociative = (CPUInfo[0] & 0x200) >> 9;
            nMaxThread = (CPUInfo[0] & 0x03ffc000) >> 14;
            nSysLineSize = (CPUInfo[1] & 0x0fff);
            nPhysicalLinePartitions = (CPUInfo[1] & 0x03ff000) >> 12;
            nWaysAssociativity = (CPUInfo[1]) >> 22;
            nNumberSets = CPUInfo[2];

            AddLog("\n");

            AddLog("\tECX Index %d\t\n", i);
            switch (nCacheType)
            {
            case 0:
                AddLog("\t   Type: Null\t\n");
                break;
            case 1:
                AddLog("\t   Type: Data Cache\t\n");
                break;
            case 2:
                AddLog("\t   Type: Instruction Cache\t\n");
                break;
            case 3:
                AddLog("\t   Type: Unified Cache\t\n");
                break;
            default:
                AddLog("\t   Type: Unknown\t\n");
            }

            AddLog("\t   Level = %d\t\n", nCacheLevel + 1);
            if (bSelfInit)
            {
                AddLog("\t   Self Initializing\t\n");
            }
            else
            {
                AddLog("\t   Not Self Initializing\t\n");
            }
            if (bFullyAssociative)
            {
                AddLog("\t   Is Fully Associatve\t\n");
            }
            else
            {
                AddLog("\t   Is Not Fully Associatve\t\n");
            }
            AddLog("\t   Max Threads = %d\t\n",
                nMaxThread + 1);
            AddLog("\t   System Line Size = %d\t\n",
                nSysLineSize + 1);
            AddLog("\t   Physical Line Partions = %d\t\n",
                nPhysicalLinePartitions + 1);
            AddLog("\t   Ways of Associativity = %d\t\n",
                nWaysAssociativity + 1);
            AddLog("\t   Number of Sets = %d\t\n",
                nNumberSets + 1);
        }

        AddLog("\t--------------------- CPU --------------------\t\n");

        float physf = (float)statex.ullTotalPhys / (1024 * 1024 * 1024);
        string phys = std::to_string(physf);

        AddLog("\tMemory: " + phys + " GB\n\n");
    #endif

    Status(0);
}

_VOID openfile(std::vector<std::string>& vect)
{
    fstream my_file;
    string file = vect[1];
    
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    my_file.open(file, ios::in);
    if (!my_file)
    {
        AddLog("No such file '" + file + "'\n");
        Status(1);
        return;
    }

    else
    {
        string str;
        while (getline(my_file, str))
        {
            AddLog(str + "\n");
        }
    }
    AddLog("\n");
    my_file.close();

    Status(0);
}

_VOID rm(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    Status(remove(vect[1].c_str()));
}

_VOID ttime(const std::vector<std::string>& vect)
{
    auto givemetime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    AddLog(ctime(&givemetime));
    Status(0);
}

_VOID whoami(const std::vector<std::string>& vect)
{
    #ifdef _WIN32
        TCHAR username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName((TCHAR*)username, &username_len);;

        char new_username[UNLEN];
        /* wcstombs(new_username, username, wcslen(username) + 1); */

        strcpy_s(new_username, UNLEN, username);
        AddLog(string(new_username) + "\n");
    #elif _WIN64
        TCHAR username[UNLEN + 1];
        DWORD username_len = UNLEN + 1;
        GetUserName((TCHAR*)username, &username_len);;

        char new_username[UNLEN];
        wcstombs(new_username, username, wcslen(username) + 1);

        AddLog(string(new_username) + "\n");
    #elif __APPLE__ || __MACH__
        char user[64];
        getlogin_r(user, 64);

        AddLog(string(user) + "\n");
    #elif __linux__
        char user[64];
        getlogin_r(user, 64);

        AddLog(string(user) + "\n");
    #elif __FreeBSD__
        char user[64];
        getlogin_r(user, 64);

        AddLog(string(user) + "\n");
    #endif

    Status(0);
}

_VOID writefile(const std::vector<std::string>& vect)
{
    if (vect.size() < 3)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    auto mode = ios::in;
    string file = vect[1];
    string content = vect[2];

    if (!std::filesystem::exists(file))
    {
        fstream new_file(file, mode);
    }

    fstream myfile(file, mode);
    myfile << content;
    myfile.close();

    Status(0);
}

/* Since we use this function for doing tests, I decided to put here some "modern C++ syntax" */
auto __cdecl yes(const std::vector<std::string>& vect) -> void
{
    /*while (true)
    {
        AddLog("yes\n");
    }*/

    AddLog("This function is test function which test connection between stuff written in Rust and C++ core!");
    AddLog("Trying to load function from Rust (rtest.dll)...\n");

    if (LoadRust("librtest.so", "rust_function", "Test argument") == 1)
    {
        AddLog("Couldn't load function from Rust!");
        AddLog("Switching to C++ code...\n");

        for (int i = 0; i < 3000; i++)
        {
            AddLog("y");
        }
    }

    Status(0);
}
