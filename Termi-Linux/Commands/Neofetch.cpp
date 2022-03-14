/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Neofetch main file
*/

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <chrono>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <limits.h>
#include <sys/unistd.h>

#include "Neofetch.h"

using namespace std;

struct Inforamtion
{
    char user[HOST_NAME_MAX];
    char computer[LOGIN_NAME_MAX];

    const char* OS;
    int uptime;

    const char* cpu;
    string memory;
} info;


int main()
{
    /* Username and computer name */
    gethostname(info.computer, HOST_NAME_MAX);
    getlogin_r(info.user, LOGIN_NAME_MAX);

    /* OS */
    #ifdef _WIN32
        info.OS = "Windows32";
    #elif _WIN64
        info.OS = "Windows64";
    #elif __APPLE__ || __MACH__
        info.OS = "Mac OSX";
    #elif __linux__
        info.OS = "GNU/Linux";
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
    vector<std::string> result = explode(line_pre_array, ':');
    cpu = result[1];
    cpu = regex_replace(cpu, regex("^ +"), "");
    info.cpu = cpu.c_str();

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
    info.uptime = uptime_seconds / 3600;


    cout << "\n";
    cout << "\t" << info.user << "@" << info.computer << "\n";
    cout << "--------------------------------------------\n";

    cout << "\n";
    cout << "\tOperating system: " << info.OS << "\t\n";
    cout << "\tUptime: " << info.uptime << " hours" << "\t\n\n";

    cout << "\tCPU: " << info.cpu << "\t\n";
    cout << "\tMemory: " << info.memory << "\t\n";
    cout << "\n";

    return 0;
}
