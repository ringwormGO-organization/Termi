// IMPORTANT STUFF
////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include "main.h"
#include "Calc.h"


#define MAX 1000

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
// ERROR MSG SCREEN IS A MESS, BUT HEY IF IT WORKD
// -StjepanBM1

int main()
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

    // command loop
    while (1)
    {
        cout << "Termi> ";
        char input[MAX];
        cin.getline(input, MAX);
        string help = "help";
        string opencalc = "opencalc";
        string geocalc = "geocalc";
        string custset = "custset";
        string filesys = "filesys";


        if (input == help)
        {
            cout << "help - shows list of commands" << endl;
            cout << "opencalc - opens a calculator" << endl;
            cout << "geocalc - opens a geometric calculator" << endl;
            cout << "filesys - opens file creation/editing" << endl;
            cout << "filesys / openfile - opens a file" << endl;
            cout << "filesys / writefile - create and edit a file" << endl;
        }

        else if (input == filesys)
        {
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
                if (!my_file) {
                    cout << "No such file" << endl;
                }

                else 
                {
                    char ch;

                    while (1) {
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

            else{
                cout << "ERROR >> COMMAND NOT FOUND" << endl;
            }

        }

        else if (input != opencalc && input != geocalc && input != filesys && input != help)
        {
            cout << "ERROR >> COMMAND NOT FOUND!" << endl;
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
                      cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
                      break;

                    case '-':
                      cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
                      break;

                    case '*':
                      cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
                      break;

                    case '/':
                      cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
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
                    char geoOPR[MAX];
                    cin.getline(geoOPR, MAX);
                    string EXT = "EXT";
                    string SUR = "SUR";
                    string TRA = "TRA";
                    string REC = "REC";
                    string SQU = "SQU";

                    if (geoOPR == "exit")
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

                    }

                }
            }
        }

    return 0;
}
