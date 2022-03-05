// IMPORTANT STUFF
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <ctime>
#include <map>
#include <filesystem>
#include <sys/stat.h>
#include <signal.h>

#include "main.h"
#include "../Programs/Include.h"

////////////////////////////////////////////////////////////////////////////////////////
// Added CD / RM / MKDIR FUNCTION
// mkdir function while inside a folder wont work! It will be fixed later
// Removed error msg until further notice
// -StjepanBM1

/* Structs */
struct sigaction sigIntHandler;

/* variable for string input */
std::string input;

/* commands list */
std::map<std::string, std::string> commands =
{
    {"help", "../Programs/bin/Help"},
    {"open-calc", "../Programs/bin/Calculator"},
    {"geocalc", "../Programs/bin/GeoCalculator"},
    {"filesys", "../Programs/bin/Filesystem"}
};

// Fucntion which control keyboards events (Ctrl-C for example)
void end(int sig)
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
        exit(sig);
    }
}

int main()
{
    using namespace std;

    cout << "ooooooooooo                              " << endl;
    cout << "    888      ooooooooooo                          o88   " << endl;
    cout << "    888      888    88  oo oooooo  oo ooo oooo   oooo  " << endl;
    cout << "    887      888ooo8     888    888 888 888 888   888 " << endl;
    cout << "    888      888    oo   888        888 888 888   888  " << endl;
    cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o " << endl;
    cout << "------------------------------------------------------- " << endl;
    cout << "           TYPE help TO SEE LIST OF ALL COMMANDS" << endl;
    cout << "          (C)2022 ringwormGO All rights reserved" << endl;
    cout << "-------------------------------------------------------  " << endl;

    /* Strings / Commands */
    string help = "help";
    string exit_command = "exit";
    string clear = "clear";
    string filesys = "filesys";
    string opencalc = "opencalc";
    string geocalc = "geocalc";

    /* Catch CTRL-C */
    sigIntHandler.sa_handler = end;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);


    /* command loop */
    while (1)
    {
        cout << "Termi> ";
        getline(cin, input);

        auto result = commands.find(input);
        const char* run;

        if (result != commands.end())
        {
            run = result->second.c_str();
            system(run);
        }

        else if (input == "clear" || input == "cls")
        {
            std::cout << "\033c";
        }

        else if (input == "exit")
        {
            exit(0);
        }

        else if (input.length() == 0) /* enter */
        {

        }
        
        else
        {
            std::cout << "'" << input << "'" << "is invalid command!\n";
        }
    }

    return 0;
}
