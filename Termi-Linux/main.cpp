#include "main.h"
#include <iostream>
#include <string>

using namespace std;

// Added mult. and devision

int main()
{

    cout << "ooooooooooo ooooooooooo                          o88   " << endl;
    cout << "88  888  88  888    88  oo oooooo  oo ooo oooo   oooo  " << endl;
    cout << "    888      888ooo8     888    888 888 888 888   888 " << endl;
    cout << "    888      888    oo   888        888 888 888   888  " << endl;
    cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o " << endl;
    cout << "-------------------------------------------------------" << endl;
    cout << "Welcome to Termi | Type help to see list of commands" << endl;

    // command loop
    while (1)
    {
        cout << "Termi> ";
        string input;
        cin >> input;
        string exit = "exit";
        string help = "help";
        string opencalc = "opencalc";

        if (input == help)
        {
            cout << "help - shows list of commands" << endl;
            cout << "opencalc - opens a calculator (it can only add numbers currently)" << endl;;
                    // Command result
        }

        else if (input == opencalc)
        {
            cout << "-----------------------------------------------------------------------------------------------" << endl;
            cout << " " << endl;
            cout << "Enter an operator (subt = subtraction | add = addition | dev = devision | mul = multiplication)" << endl;
            cout << "Type exit to exit calculator" << endl;
            cout << " " << endl;
            cout << "-----------------------------------------------------------------------------------------------" << endl;
            while(1)
            {
                cout << "calc > ";
                string inpOPR;
                cin >> inpOPR;
                string subt = "subt";
                string add = "add";
                string dev = "dev";
                string mul = "mul";


                if (inpOPR == subt)
                {
                    double x, y;
                    double res;
                    cout << "Type a number: ";
                    cin >> x;
                    cout << "Type a  second number: ";
                    cin >> y;
                    cout << "Result: "
                    << subOfTwoNumbers(x, y)
                    << endl;

                }

                else if (inpOPR == add)
                {
                    double x, y;
                    double res;
                    cout << "Type a number: ";
                    cin >> x;
                    cout << "Type a second number: ";
                    cin >> y;
                    cout << "Result: "
                    << sumOfTwoNumbers(x, y)
                    << endl;

                }

                else if (inpOPR == mul)
                {
                    double x, y;
                    double res;
                    cout << "Type a number: ";
                    cin >> x;
                    cout << "Type a second number: ";
                    cin >> y;
                    cout << "Result: "
                    << mulOfTwoNumbers(x, y)
                    << endl;

                }

                else if (inpOPR == dev)
                {
                    double x, y;
                    double res;
                    cout << "Type a number: ";
                    cin >> x;
                    cout << "Type a second number: ";
                    cin >> y;
                    cout << "Result: "
                    << devOfTwoNumbers(x, y)
                    << endl;

                }

                else if (inpOPR == exit)
                {
                    break;
                }
                else
                {
                    cout << "ERROR = COMMAND NOT CORRECT / IT DOSENT EXIST" << endl;
                }
            }
        }

        else
        {
        cout <<  "Command not found" << endl;
                // Wrong command entered
        }

    }

    return 0;
}
