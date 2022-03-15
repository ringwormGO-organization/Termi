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
#include <cstdlib>

#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <lmcons.h>

#include "Neofetch.h"
#include "CPU.h"

#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "Kernel32.lib")

using namespace std;

/*
 * Return version of Windows operating system
 *
 * In own function
*/
const char* OperatingSystem()
{
    OSVERSIONINFO vi;
    vi.dwOSVersionInfoSize = sizeof(vi);
    if (GetVersionEx(&vi) == 0) 
    {
        cout << "Cannot get OS version information!\n";
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

/* Uptime part - in own functions */
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

int main()
{
    /* Username and computer name */
    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserName((TCHAR*)username, &username_len);

    TCHAR computer[UNLEN + 1];
    DWORD computer_len = UNLEN + 1;
    GetComputerName((TCHAR*)computer, &computer_len);

    /* Memory */
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);

    cout << "\n";
    wcout << "\t" << username << "@" << computer << "\n";
    cout << "--------------------------------------------\n";

    cout << "\n";
    cout << "\tOperating system: " << OperatingSystem() << "\t\n";

    if (UptimeH() < 1)
    {
        cout << "\tUptime: " << UptimeM() << " minutes" << "\t\n";
    }
    else
    {
        cout << "\tUptime: " << UptimeH() << " hours" << "\t\n";
    }


    cout << "\t ---------------- CPU ----------------\n";
	cout << "\tVendor.............................: " << GetVendorID() << "\t\n";
	cout << "\tHighest supported CPUID subfunction: " << GetHighestFunction() << "\t\n";
	X86CPUInfo CPUInfo;
	GetCPUInfo(CPUInfo);
	cout << "\tStepping...........................: " << CPUInfo.Stepping << "\t\n";
	cout << "\tModel..............................: " << CPUInfo.Model << "\t\n";
	cout << "\tFamily.............................: " << CPUInfo.Family << "\t\n";
	cout << "\tType...............................: " << CPUInfo.Type << "\t\n";
	cout << "\tExtended Model.....................: " << CPUInfo.ExtendedModel << "\t\n";
	cout << "\tExtended Family....................: " << CPUInfo.ExtendedFamily << "\t\n";
    cout << "\t ---------------- CPU ----------------\n";

    cout << "\tMemory: " << (float)statex.ullTotalPhys / (1024 * 1024 * 1024) << " GB" << "\t\n";
    cout << "\n";

    return 0;
}
