#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <Windows.h>

#include "Calc.h"
#include "Check.hpp"

#define MAX 250

#define VERSION_MAJOR "0"
#define VERSION_MINOR "1"
#define VERSION_PATCH "3"
#define VERSION "v" VERSION_MAJOR "." VERSION_MINOR "." VERSION_PATCH

std::string input;

void Welcome()
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

int main()
{
    using namespace std;

    Welcome();

    while (true)
    {
        cout << "Termi> ";
        getline(cin, input);
        check(input);
    }

    return 0;
}