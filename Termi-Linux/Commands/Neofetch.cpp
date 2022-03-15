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
#include <algorithm>
#include <filesystem>

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

    string OS;
    int uptime;

    string cpu;
    string memory;
} info;

static string extract(string file) 
{
    string distro;
    string line_pre_array = parse("PRETTY_NAME", file);
    vector<string> result = explode(line_pre_array, '=');
    distro = result[1]; // Second element.
    // Trim `"` from the string.
    distro.erase(remove(distro.begin(), distro.end(), '\"'), distro.end());
    return distro;
}

/* 
 * Parse `/etc/os-release` for the PRETTY_NAME string
 * and extract the value of the variable.
 * Returns the name of the distro.
 * Example: Gentoo/Linux.
 * 
 * In own function
*/
static string distro() 
{
    // Check if running Android.
    if (system("which getprop > /dev/null 2>&1")) 
    {
        // No getprop command, resume as normal.
        filesystem::path bedrock_file = "/bedrock/etc/os-release";
        filesystem::path normal_file = "/etc/os-release";
        filesystem::path weird_file = "/var/lib/os-release";
        if (filesystem::exists(bedrock_file)) 
        {
            return extract("/bedrock/etc/os-release");
        } else if (filesystem::exists(normal_file)) 
        {
            return extract("/etc/os-release");
        } else if (filesystem::exists(weird_file)) 
        {
            return extract("/var/lib/os-release");
        } 
        else 
        {
            return "N/A (could not read '/bedrock/etc/os-release', '/etc/os-release', nor '/var/lib/os-release')";
        }
    } 
    else 
    {
        // getprop command found, return Android version.
        const string& command = "getprop ro.build.version.release";
        system((command + " > temp.txt").c_str());
 
        ifstream ifs("temp.txt");
        string ret{istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
        ifs.close(); // must close the inout stream so the file can be cleaned up
        if (remove("temp.txt") != 0) 
        {
            perror("Error deleting temporary file");
        }
        string message = "Android " + ret;
        message.erase(remove(message.begin(), message.end(), '\n'), message.end());
        return message;
    }
}

/* 
 * Run the command and count the lines of output, 
 * optionally subtract from the count to account for extra lines,
 * then assemble and return the message as a string.
 * 
 * In own function
*/
static string count(string cmd, string manager, int remove = 0) 
{
    const string& command = cmd + "| wc -l";
    system((command + " > temp.txt").c_str());
 
    ifstream ifs("temp.txt");
    string ret{ istreambuf_iterator<char>(ifs), istreambuf_iterator<char>() };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) 
    {
        perror("Error deleting temporary file");
    }
    int amount = stoi(ret);
    amount = amount - remove;
    string message = ret + " (" + manager + ")";
    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
    return message;
}

static PackageManager findPackageManager() 
{
    if (system("which apk > /dev/null 2>&1") == 0) 
    {
        return APK;
    } 

    else if (system("which dnf > /dev/null 2>&1") == 0) 
    {
        return DNF;
    } 

    else if (system("which dpkg-query > /dev/null 2>&1") == 0) 
    {
        return DPKG;
    } 

    else if (system("which eopkg > /dev/null 2>&1") == 0) 
    {
        return EOPKG;
    } 

    else if (system("which pacman > /dev/null 2>&1") == 0) 
    {
        return PACMAN;
    } 

    else if (system("which pkg > /dev/null 2>&1") == 0) {

        return PKG;
    } 

    else if (system("which qlist > /dev/null 2>&1") == 0) 
    {
        return QLIST;
    } 

    else if (system("which rpm > /dev/null 2>&1") == 0) 
    {
        return RPM;
    } 

    else if (system("which xbps-query > /dev/null 2>&1") == 0) 
    {
        return XBPS;
    } 

    else 
    {
        return UNKNOWN;
    }
}

/* Return package counts */
string packages() 
{
    switch (findPackageManager()) 
    {
        case APK:
            return count("apk info", "apk");
        case DNF:
            return count("dnf list installed", "dnf");
        case DPKG:
            return count("dpkg-query -f '${binary:Package}\n' -W", "dpkg");
        case EOPKG:
            return count("eopkg list-installed", "eopkg");
        case PACMAN:
            return count("pacman -Qq", "pacman");
        case PKG:
            return count("pkg -l", "Portage");
        case QLIST:
            return count("qlist -I", "Portage");
        case RPM:
            return count("rpm -qa", "rpm");
        case XBPS:
            return count("xbps-query -l", "xbps");
        default: return "N/A (no supported pacakge managers found)";
    }
}


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
    info.uptime = uptime_seconds / 3600;


    cout << "\n";
    cout << "\t" << info.user << "@" << info.computer << "\n";
    cout << "--------------------------------------------\n";

    cout << "\n";
    cout << "\tOperating system: " << info.OS  << ", " << distro() << "\t\n";
    cout << "\tUptime: " << info.uptime << " hours" << "\t\n\n";
    cout << "\tPackages: " << packages() << "\t\n";

    cout << "\tCPU: " << info.cpu << "\t\n";
    cout << "\tMemory: " << info.memory << "\t\n";
    cout << "\n";

    return 0;
}
