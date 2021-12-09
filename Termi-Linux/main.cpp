#include <iostream>
#include "main.h"

using namespace std;

// should make the code prettier ( and it should prob be more organized) but I guess it's fine?
// P.S I suck at organization
// - StjepanBM1

int main()
{

    cout << "Welcome to Termi | Type help to see list of commands" << endl;
    string input;
    cin >> input;
    string help = "help";
    string test = "test";

    if (input == help)
    {
        cout << "help - shows list of commands" << endl;
        cout << "test - just a test command" << endl;
                // Command result
    }

    else if (input == test)
    {
        cout << "Testcommand working fine" << endl;
                // Command result
    }

    else
    {
    cout <<  "Command not found" << endl;
              // Wrong command entered
    }

    return 0;
}
