/**
 * @author Stjepan Bilić Matišić
 * PROJECT: Termi-Linux version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file for Linux Version
*/

// IMPORTANT STUFF
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <exception>
#include <memory>
#include <map>
#include <filesystem>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>


#define MAX 1000
#define MAX_FILE 25

#define VERSION_MAJOR "0"
#define VERSION_MINOR "1"
#define VERSION_PATCH "7"
#define VERSION "v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Andrej's update for Termi-Linux was a mess.
// As a result some functions have been removed until further notice
// Thank you for understanding
// -StjepanBM1

/* Functions */


/* Structs */
struct sigaction sigIntHandler;

/* variable for string input */
std::string input;

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

std::map<std::string, std::string> commands = 
{
    {"open-calc", "./bin/OpenCalc"},
    {"geocalc", "./bin/GeoCalc"},
    {"filesys", "./bin/filesys"},
};

int main()
{

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

    // command loop
    while (1)
    {
        cout << "Termi> ";
        getline(cin, input);

        // Catch CTRL-C
        sigIntHandler.sa_handler = end;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;
        sigaction(SIGINT, &sigIntHandler, NULL);


        auto result = commands.find(input);
        const char* run;

        if (result != commands.end())
        {
            run = result->second.c_str();
            system(run);
        }

        else if (input == "help")
        {
            cout << "help - shows list of commands" << endl;
            cout << "opencalc - opens a calculator" << endl;
            cout << "geocalc - opens a geometric calculator" << endl;
            cout << "clear or cls - clear console" << endl;
            cout << "exit - closes Termi" << endl;
            cout << "----------FILESYS COMMANDS" << endl;
            cout << "filesys - opens file creation/editing" << endl;
            cout << "filesys / openfile - opens a file" << endl;
            cout << "filesys / writefile - create and edit a file" << endl;
            cout << "filesys / mkdir - make a directory" << endl;
            cout << "filesys / cd - cd into a directory" << endl;
            cout << "filesys / rm - removes a file" << endl;
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
            std::cout << "'" << input << "'" << " is invalid command!\n";
        }
    }
}
