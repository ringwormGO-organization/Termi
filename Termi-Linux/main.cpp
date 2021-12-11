#include "main.h"
#include <iostream>
#include <string>

using namespace std;

/̶/̶ ̶s̶h̶o̶u̶l̶d̶ ̶m̶a̶k̶e̶ ̶t̶h̶e̶ ̶c̶o̶d̶e̶ ̶p̶r̶e̶t̶t̶i̶e̶r̶ ̶(̶ ̶a̶n̶d̶ ̶i̶t̶ ̶s̶h̶o̶u̶l̶d̶ ̶p̶r̶o̶b̶ ̶b̶e̶ ̶m̶o̶r̶e̶ ̶o̶r̶g̶a̶n̶i̶z̶e̶d̶)̶ ̶b̶u̶t̶ ̶I̶ ̶g̶u̶e̶s̶s̶ ̶i̶t̶'̶s̶ ̶f̶i̶n̶e̶?̶ ̶
/̶/̶ ̶P̶.̶S̶ ̶I̶ ̶s̶u̶c̶k̶ ̶a̶t̶ ̶o̶r̶g̶a̶n̶i̶z̶a̶t̶i̶o̶n̶ ̶
/̶/̶ ̶-̶ ̶S̶t̶j̶e̶p̶a̶n̶B̶M̶1̶


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
