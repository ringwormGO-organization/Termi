/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Help main file
*/

#include "Include.h"

//Print help
int main(int argc, char** argv)
{
    using namespace std;

    cout << "help - shows list of commands" << endl;
    cout << "opencalc - opens a calculator" << endl;
    cout << "geocalc - opens a geometric calculator" << endl;
    cout << "filesys - opens file creation/editing" << endl;
    cout << "filesys / openfile - opens a file" << endl;
    cout << "filesys / writefile - create and edit a file" << endl;
    cout << "filesys / mkdir - make a directory" << endl;
    cout << "filesys / cd - cd into a directory" << endl;
    cout << "filesys / rm - removes a file" << endl;

    return 0;
}