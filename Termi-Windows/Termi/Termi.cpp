#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "windows.h"

#include "Termi.h"
#include "Header.h"
#include "Commands.h"

#define MAX 100

using namespace std;

extern void Floppy()
{
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

extern void Calculator(double num1, char operation, double num2)
{
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
    cout << "help > this" << endl;
    cout << "calculator > open calculator" << endl;
    cout << "exit > exit Termi" << endl;
    cout << "floppy > print floppy" << endl;
    cout << "geo-calculator > open geo calculator" << endl;
}