#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

#include <Windows.h>

#define MAX 250

#define VERSION_MAJOR "0"
#define VERSION_MINOR "1"
#define VERSION_PATCH "9"
#define VERSION "v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

std::string input;

BOOL WINAPI end(DWORD signal)
{
    if (signal == CTRL_C_EVENT)
    {
        std::cout << "\nPress any key to continue...\n";
        auto key = std::cin.get();
        if (key != 10)
        {
            /* we need to do something here; input is broken */
            exit(0);
        }
        else
        {
            exit(signal);
        }
    }

    return TRUE;
}

std::map<std::string, std::string> commands =
{
    {"help", "Programs\\bin\\help.exe"},
    {"open-calc", "Programs\\bin\\OpenCalc.exe"},
    {"geocalc", "Programs\\bin\\GeoCalc.exe"},
    {"filesys", "Programs\\bin\\filesys.exe"},
    {"neofetch", "Programs\\bin\\Neofetch.exe"},
};

void Check(std::string command)
{
    auto result = commands.find(command);

    const char* run;

    if (result != commands.end())
    {
        run = result->second.c_str();
        system(run);
    }

    else if(command == "clear" || command == "cls")
    {
        std::cout << "\033c";
    }

    else if (command == "exit")
    {
        exit(0);
    }

    else if (command.length() == 0) /* enter */
    {

    }

    else
    {
        std::cout << "'" << command << "'" << " is invalid command!\n";
    }
}

int main()
{
    using namespace std;

    cout << "ooooooooooo                              " << endl;
    cout << "    888      ooooooooooo                          o88   " << endl;
    cout << "    888      888    88  oo oooooo  oo ooo oooo   oooo  " << endl;
    cout << "    888      888ooo8     888    888 888 888 888   888 " << endl;
    cout << "    888      888    oo   888        888 888 888   888  " << endl;
    cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o " << endl;
    cout << "------------------------------------------------------- " << endl;
    cout << "           TYPE help TO SEE LIST OF ALL COMMANDS" << endl;
    cout << "          (C)2022 ringwormGO All rights reserved" << endl;
    cout << "-------------------------------------------------------  " << endl;

    while (true)
    {
        cout << "Termi> ";
        getline(cin, input);
        Check(input);
    }

    return 0;
}
