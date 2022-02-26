#include <iostream>
#include <fstream>
#include <cstring>
#include <Windows.h>

#include "Termi.h"
#include "Header.h"
#include "Commands.h"

#define MAX 250

#define VERSION_MAJOR "0"
#define VERSION_MINOR "1"
#define VERSION_PATCH "2"
#define VERSION "v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

extern void Floppy()
{
    using namespace std;

    cout <<"%%%%&&&&..............%%%/  " << endl << 
                "%%%%&&&&.........&&&..%%%%%   " << endl << 
                "%%%%&&&&.........&&&..%%%%%%%" << endl << 
                "%%%%&&&&.........&&&..%%%%%%% " << endl <<
                "%%%%&&&&.........&&&..%%%%%%% " << endl <<
                "%%%%&&&&.........,,,..%%%%%%%" << endl <<
                "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl <<
                "%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << endl <<
                "%%%%  _________________ .%%%%" << endl <<
                "%%%%  _________________ .%%%%" << endl <<
                "%%%%  _________________ .%%%%" << endl <<
                "%%%%  _________________ .%%%%" << endl <<
                "%%%%  _________________ .%%%%" << endl <<
                "%%%%  _________________ .%%%%" << endl <<
                "%&&%                    ,%&&%" << endl <<
                "%&&%%%%%%%%%%%%%%%%%%%%%%%&&%" << endl <<
                "%&&%%%%%%%%%%%%%%%%%%%%%%%&&%" << endl;
}

extern void Calculator()
{
    using namespace std;

    double num1, num2;
    char operation;

    cout << "Type two numbers and operator\n";
    cin >> num1 >> num2 >> operation;

    switch (operation)
    {
        case '+':
        {
            double sum = sumOfTwoNumbers(num1, num2);
            cout << sum << '\n';
            break;
        }

        case '-':
        {
            double sub = subOfTwoNumbers(num1, num2);
            cout << sub << '\n';
            break;
        }

        case '*':
        {
            double mul = mulOfTwoNumbers(num1, num2);
            cout << mul << '\n';
            break;
        }

        case '/':
        {
            double dev = devOfTwoNumbers(num1, num2);
            cout << dev << '\n';
            break;
        }

        case 'x':
        {
            break;
        }

        default:
        {
            cout << "Operator invalid!\n\n";
            break;
        }
    }
}

extern void GeoCalc()
{
    using namespace std;

    string calccho;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << " " << endl;
    cout << "TYPE GEO TO START" << endl;
    cout << "Type exit to exit calculator" << endl;
    cout << "Measuring unit: cm" << endl;
    cout << " " << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "> ";
    cin >> calccho;

    if (calccho == GEO)
    {
        while (1)
        {
            cout << "Enter what to do (EXT = extent |SUR = surface area )";

            cout << "geocalc > ";
            string geoOPR;
            cin >> geoOPR;

            if (geoOPR == exit2)
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
                    double x, y;
                    double res;
                    cout << "Enter the length of first side : ";
                    cin >> x;
                    cout << "Enter the length of second side : ";
                    cin >> y;
                    cout << "Result: "
                        << povrsDvijustr(x, y)
                        << "cm2"
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
                        << "cm2"
                        << endl;
                }
            }

            else if (geoOPR == EXT)
            {
                cout << "SELECT WHAT GEOMETRIC CHARCTER YOU WANT" << endl;
                cout << "TRA = TRIANGLE | REC = RECTANGLE | SQU = SQUARE" << endl;
                cout << "> ";

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
                        << "cm"
                        << endl;
                }

                else if (extOPR == REC)
                {
                    double x, y;
                    double res;
                    cout << "Enter the length of first side : ";
                    cin >> x;
                    cout << "Enter the length of second side : ";
                    cin >> y;
                    cout << "Result: "
                        << opsgDvijustr(x, y)
                        << "cm"
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
                        << opsgKvdjustr(x, sqe)
                        << endl;

                }
            }
        }
    }
    else if (calccho == exit2)
    {
        
    }
    else
    {

    }
}

extern void Welcome()
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
}

extern void Help() 
{
    using namespace std;

    cout << "Core (first command) is programmed in C++ but other functions which are programmed in" <<
        " C# may require - to use it.\nExample: filesys-mkdir" << endl << endl;

    cout << "help - shows list of commands (programmed in C++)" << endl;
    cout << "calculator - opens a calculator (programmed in C++)" << endl;
    cout << "geo-calc - opens a geometric calculator (programmed in C++)" << endl;
    cout << "floppy > print floppy (programmed in C++)" << endl;
    cout << "exit > exit Termi (programmed in C#)" << endl;
    cout << "filesys - opens file creation/editing (programmed in C++)" << endl;
    cout << "filesys / openfile - opens a file (programmed in C++)" << endl;
    cout << "filesys / writefile - create and edit a file (programmed in C++)" << endl << endl;
}

extern void Filesystem()
{
    using namespace std;

    cout << "FILESYS> ";
    char input1[MAX];
    cin.getline(input1, MAX);
    string openfile = "openfile";
    string writefile = "writefile";

    if (input1 == openfile)
    {
        fstream my_file;
        cout << "OPENFILE> ";
        char input2[MAX];
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

    else if (input1 == writefile)
    {
        cout << "WRITEFILE> ";
        char input4[MAX];
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
}