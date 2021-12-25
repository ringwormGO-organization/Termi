#include "main.h"
#include "Calc.h"
#include <iostream>
#include <string>
#include <ctime>


using namespace std;

// I updated the calculator!
// We should add function where user can edit files!
// - StjepanBM1

int main()
{

    cout << "ooooooooooo ooooooooooo                          o88    " << endl;
    cout << "88  888  88  888    88  oo oooooo  oo ooo oooo   oooo   " << endl;
    cout << "    888      888ooo8     888    888 888 888 888   888   " << endl;
    cout << "    888      888    oo   888        888 888 888   888   " << endl;
    cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o  " << endl;
    cout << "------------------------------------------------------- " << endl;
    cout << "           TYPE help TO SEE LIST OF ALL COMMANDS" << endl;
    cout << "          ©2021 ringwormGO all rights reserved" << endl;
    cout << "-------------------------------------------------------  " << endl;

    // command loop
    while (1)
    {
        //cout << "Type Enter to start Termi" << endl;
        string input;
        cin >> input;
        string exit = "exit";
        string help = "help";
        string opencalc = "opencalc";
        string geocalc = "geocalc";
        string custset = "custset";


        if (input == help)
        {
            cout << "help - shows list of commands" << endl;
            cout << "opencalc - opens a calculator" << endl;;
            cout << "geocalc - opens a geometric calculator" << endl;;
            cout << "custset -  [CURRENTLY NOT IN USE] opens user settings" << endl;;
                    // Command result
        }

        else if (input == opencalc)
        {

                char op;
                float num1, num2;

                cout << "Enter operator: +, -, *, /: ";
                cin >> op;

                cout << "Enter the first number: ";
                cin >> num1;
                cout << "Enter the second number: ";
                cin >> num2;

                switch(op) {

                    case '+':
                      cout << num1 << " + " << num2 << " = " << num1 + num2;
                      break;

                    case '-':
                      cout << num1 << " - " << num2 << " = " << num1 - num2;
                      break;

                    case '*':
                      cout << num1 << " * " << num2 << " = " << num1 * num2;
                      break;

                    case '/':
                      cout << num1 << " / " << num2 << " = " << num1 / num2;
                      break;

                    default:
                      // If the operator is other than +, -, * or /, error message is shown
                      cout << "Error! operator is not correct";
                      break;
                  }
        }



        else if (input == geocalc)
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
                    string geoOPR;
                    cin >> geoOPR;
                    string EXT = "EXT";
                    string SUR = "SUR";
                    string TRA = "TRA";
                    string REC = "REC";
                    string SQU = "SQU";

                    if (geoOPR == SUR)
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

                        else
                        {
                            break;
                        }


                    }


                }




            }
        }

    return 0;
}
