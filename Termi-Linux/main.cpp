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
#include <filesystem>
#include <sys/stat.h>
#include <signal.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#include "Calc.h"

#define MAX 1000
#define MAX_FILE 25

#define VERSION_MAJOR "0"
#define VERSION_MINOR "1"
#define VERSION_PATCH "4"
#define VERSION "v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// Andrej's update for Termi-Linux was a mess.
// As a result some functions have been removed until further notice
// Thank you for understanding
// -StjepanBM1

/* Functions */

void Filesys()
{
    cout << "FILESYS> ";
    char input1[MAX];
    cin.getline(input1, MAX);
    string openfile = "openfile";
    string writefile = "writefile";
    string rm = "rm";
    string mdkir = "mkdir";
    string rmdir = "rmdir";
    string cd = "cd";

    if (input1 == openfile)
    {
        fstream my_file;
        cout << "OPENFILE> ";
        char input2[MAX_FILE];
        cin.getline(input2, MAX);
        my_file.open(input2, ios::in);
        if (!my_file) 
        {
            cout << "No such file" << endl;
        }

        else 
        {
            char ch;

            while (1) 
            {
                my_file >> ch;
                if (my_file.eof())
                    break;

                cout << ch;
            }

        }
        my_file.close();
    }

    else if (input1 == list)
    {
        cout << "LIST: ";
        DIR *dr;
        struct dirent *en;
        dr = opendir("."); //open all directory
        if (dr) {
            while ((en = readdir(dr)) != NULL) 
            {
                cout << "   \n"<< en->d_name; //print all directory name
            }
            closedir(dr); //close all directory
                cout << "\n" << endl;
        }
    }
    

    else if (input1 == writefile)
    {
        cout << "WRITEFILE> ";
        char input4[MAX_FILE];
        cin.getline(input4, MAX);

        ofstream MyFile(input4);

        // Write to the file
        cout << "What do you want your file to contain?" << endl;
        cout << "/> ";
        char input5[MAX];
        cin.getline(input5, MAX);
        MyFile << input5;

        // Close the file
        MyFile.close();
    }

    else if (input1 == mdkir)
    {
        cout << "mkdir~/ ";
        char input6[MAX_FILE];
        cin.getline(input6, MAX);

        if (mkdir(input6, 0777) == -1)
        {
            cerr << "Error :  " << strerror(errno) << endl;
        }

        else
        {
            cout << "Directory created" << endl;
        }
    }
    
    else if (input1 == cd)
    {
        cout << "cd~/ ";
        char input7[MAX_FILE];
        cin.getline(input7, MAX);
        int chdir(const char *input7);

        cout << input7;
        char input8[MAX];
        cin.getline(input7, MAX);
    }

    else if (input1 == rm)
    {
        cout << "rm~/ ";
        char input9[MAX_FILE];
        cin.getline(input9, MAX);

        int result = remove(input9);
    }

    else
    {
        cout << "ERROR >> COMMAND NOT FOUND" << endl;
    }
}

void OpenCalc()
{
    char op;
    float num1, num2;

    cout << "Enter operator: +, -, *, /: ";
    cin >> op;

    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    switch(op) 
    {
        case '+':
            cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
            break;

        case '-':
            cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
            break;

        case '*':
            cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
            break;

        case '/':
            cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
            break;

        default:
            // If the operator is other than +, -, * or /, error message is shown
            cout << "Error! operator is not correct";
            break;
        }
}

void GeoCalc()
{
    string calccho;
    string GEO = "GEO";
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << " " << endl;
    cout << "TYPE GEO TO START" << endl;
    cout << "Type exit to exit calculator" << endl;
    cout << " " << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "> ";
    cin >> calccho;

    if (calccho == GEO)
        while(1)
        {
            cout << "Enter what to do (EXT = extent |SUR = surface area )";

            cout << "geocalc > ";
            char geoOPR[MAX];
            cin.getline(geoOPR, MAX);
            string EXT = "EXT";
            string SUR = "SUR";
            string TRA = "TRA";
            string REC = "REC";
            string SQU = "SQU";

            if (geoOPR == "exit")
            {

            }

            else if(geoOPR == SUR)
            {
                cout << "SELECT WHAT GEOMETRIC CHARCTER YOU WANT" << endl;
                cout << "REC = RECTANGLE | SQU = SQUARE" << endl;
                cout << "> ";
                string TRA = "TRA";
                string REC = "REC";
                string SQU = "SQU";
                string surOPR;
                cin >> surOPR;

                if (surOPR == REC)
                {
                    double x,y;
                    double res;
                    cout << "Enter the length of first side : ";
                    cin >> x;
                    cout << "Enter the length of second side : ";
                    cin >> y;
                    cout << "Result: "
                    << povrsDvijustr(x, y)
                    << endl;
                }

                else if (surOPR == SQU)
                {
                    double x;
                    double res;
                    cout << "Enter the length of one side : ";
                    cin >> x;
                    cout << "Result : "
                    << povrsKvdjustr(x)
                    << endl;
                }
            }

            else if (geoOPR == EXT)
            {
                cout << "SELECT WHAT GEOMETRIC CHARCTER YOU WANT" << endl;
                cout << "TRA = TRIANGLE | REC = RECTANGLE | SQU = SQUARE" << endl;
                cout << "> ";
                string TRA = "TRA";
                string REC = "REC";
                string SQU = "SQU";
                string extOPR;
                cin >> extOPR;

                if (extOPR == TRA)
                {
                    double x, y, z;
                    double res;
                    cout << "Enter the length of first side : ";
                    cin >> x;
                    cout << "Enter the length of second side : ";
                    cin >> y;
                    cout << "Enter the length of third side : ";
                    cin >> z;
                    cout << "Result: "
                    << opsgTrijustr(x, y, z)
                    << endl;
                }

                else if (extOPR == REC)
                {
                    double x,y;
                    double res;
                    cout << "Enter the length of first side : ";
                    cin >> x;
                    cout << "Enter the length of second side : ";
                    cin >> y;
                    cout << "Result: "
                    << opsgDvijustr(x, y)
                    << endl;
                }

                else if (extOPR == SQU)
                {
                    double x;
                    int sqe;
                    sqe = 4;
                    double res;
                    cout << "Enter the length of one side : ";
                    cin >> x;
                    cout << "Result : "
                    << opsgKvdjustr(x,sqe)
                    << endl;

                }
                /* wrong command */
                else
                {
                    
                }
            }

        }
    }
}

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

int main(void)
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

        // Strings / Commands
        string help = "help";
        string exit = "exit";
        string clear = "clear";
        string filesys = "filesys";
        string list = "list";
        string opencalc = "opencalc";
        string geocalc = "geocalc";

        // Catch CTRL-C
        sigIntHandler.sa_handler = end;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;
        sigaction(SIGINT, &sigIntHandler, NULL);


        if (input == help)
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

        else if (input == filesys)
        {
            Filesys();
        }

        else if (input == opencalc)
        {
            OpenCalc();                
        }


        else if (input == geocalc)
        {
            GeoCalc();
        }

        else if (input == clear || input == "cls")
        {
            cout << "\033c";
        }

        else if (input == exit)
        {
            return(0);
        }

        else if (input.length() == 0) /* enter */
        {

        }

        else
        {
            std::cout << "'" << input << "'" << "is invalid command!\n";
        }


    return 0;
}
