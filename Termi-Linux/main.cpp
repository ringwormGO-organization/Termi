// IMPORTANT STUFF
////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Commands.h"

////////////////////////////////////////////////////////////////////////////////////////
// ERROR MSG SCREEN IS A MESS, BUT HEY IF IT WORKD
// -StjepanBM1

std::string help2 = "help";
std::string opencalc2 = "opencalc";
std::string geocalc2 = "geocalc";
std::string custset2 = "custset";
std::string filesys2 = "filesys";

int main()
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

    // command loop
    while (1)
    {
        cout << "Termi> ";
        char input[MAX];
        cin.getline(input, MAX);

        if (input == help2)
        {
            Help();
        }

        else if (input == filesys2)
        {
            Filesys();
        }

        else if (input == opencalc2)
        {
            OpenCalc();
        }


        else if (input == geocalc2)
        {
            GeoCalc();
        }
        
        else
        {
            cout << "ERROR >> COMMAND NOT FOUND" << endl;
        }
    }

    return 0;
}
