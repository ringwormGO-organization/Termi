/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file for implementing core commands code
*/

#include "Export.h"

#include "Commands/base64.hpp"
#include "Commands/sysfetch.hpp"
#include "Commands/filesys.hpp"
#include "Commands/ping.hpp"
#include "Commands/Geocalc.h"

#include <iostream>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

#include <dlfcn.h>

using namespace std;

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

    func = dlsym(handle, function);
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

    func = dlsym(handle, "tmain");
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
        fputs (dlerror(), stderr);
        puts(" ");
        exit(1);
    }

    func = dlsym(handle, function);
    if ((error = dlerror()) != NULL)  {
        printf("%s\n", error);
        return 1;
    }

    (*func)(value);
    dlclose(handle);

    return 0;
}

void AddLog(std::string fmt, ...)
{
    LoadSO("AddLog", fmt.c_str());
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

/* ------------------------------------------------------------------------------------------ */

void base64(const std::vector<std::string>& vect)
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

void calc(const std::vector<std::string>& vect)
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
    catch (...)
    {
        Status(2);
    }
}

void cd(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    Status(chdir(vect[1].c_str()));
}

void change_setting(const std::vector<std::string>& vect)
{
    if (vect.size() < 3)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    int setting = stoi(vect[1]);

    try
    {
        if (setting != 5 && setting != 8)
        {
            LoadSO(setting, stof(vect[2]));
        }

        else if (setting == 5)
        {
            LoadSO("SetFontName", vect[2].c_str());
            LoadSO(5, 0);
        }

        else if (setting == 8)
        {
            LoadSO("SetStartupCommand", vect[2].c_str());
            LoadSO(8, 0);
        }
    }

    catch (...)
    {
        Status(2);
    }
}

void echo(const std::vector<std::string>& vect)
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

void find_command(const std::vector<std::string>& vect)
{
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
}

void geocalc(const std::vector<std::string>& vect)
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

    catch (...)
    {
        Status(2);
    }
}

void list_dir(const std::vector<std::string>& vect)
{
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

    Status(0);
}

void new_dir(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

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
}

void sysfetch(const std::vector<std::string>& vect)
{
    /* Username and computer name */
    gethostname(info.computer, 64);
    getlogin_r(info.user, 256);

    /* OS */
    #ifdef _WIN32
        info.OS = "Windows32";
    #elif _WIN64
        info.OS = "Windows64";
    #elif __APPLE__ || __MACH__
        info.OS = "Mac OSX";
    #elif __linux__
        info.OS = "(GNU/)Linux";
    #elif __FreeBSD__
        info.OS = "FreeBSD";
    #elif __unix || __unix__
        info.OS = "Unix";
    #else
        info.OS = "Other";
    #endif

    /* CPU */
    string cpu;
    string line_pre_array = parse("model name", "/proc/cpuinfo");
    vector<string> result = explode(line_pre_array, ':');
    cpu = result[1];
    cpu = regex_replace(cpu, regex("^ +"), "");
    info.cpu = cpu;

    /* Memory */
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

    /* Uptime */
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
    Status(0);
}

void openfile(std::vector<std::string>& vect)
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

void ping(const std::vector<std::string>& vect)
{
    try
    {
        if (vect.size() < 2)
        {
            AddLog("Not enough arguments!");
            Status(1);
            return;
        }

        if (_ping(vect[1].c_str()))
        {
            AddLog("$gPing is OK!");
        }

        else
        {
            AddLog("$rPing is NOT OK!");
        }

        Status(0);
    }

    catch(...)
    {
        Status(2);
        return;
    }
}

void rm(const std::vector<std::string>& vect)
{
    if (vect.size() < 2)
    {
        AddLog("Not enough arguments!");
        Status(1);
        return;
    }

    Status(remove(vect[1].c_str()));
}

void ttime(const std::vector<std::string>& vect)
{
    auto givemetime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    AddLog(ctime(&givemetime));
    Status(0);
}

void whoami(const std::vector<std::string>& vect)
{
    char user[64];
    getlogin_r(user, 64);

    AddLog(string(user) + "\n");
    Status(0);
}

void writefile(const std::vector<std::string>& vect)
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

void yes(const std::vector<std::string>& vect)
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
