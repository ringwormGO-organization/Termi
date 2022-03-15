/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version
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
#include <limits.h>

#include "Neofetch.h"

using namespace std;

struct Inforamtion
{
    char user[4096];
    char computer[4096];

    const char* OS;
    int uptime;

    const char* cpu;
    string memory;
} info;


int main()
{
    /* Username and computer name */


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
    

    /* Memory */

    /* Uptime */


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
