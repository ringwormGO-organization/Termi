#include "main.h"
#include <iostream>
#include <string>

using namespace std;

// I really should start putting stuff inside main.h

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
        string help = "help";
        string opencalc = "opencalc";

        if (input == help)
        {
            cout << "help - shows list of commands" << endl;
            cout << "opencalc - opens a calculator (it can only add numbers currently)" << endl;
                    // Command result
        }

        else if (input == opencalc)
        {
            int a, b;
            int res;
            cout << "Type a number: ";
            cin >> a;
            cout << "Type another number: ";
            cin >> b;
            res = a + b;
            cout << "Result: " << res << endl;
   
        }

        else
        {
        cout <<  "Command not found" << endl;
                // Wrong command entered
        }

    }
    
    return 0;
}
