/**
 * @author Stjepan Bilić Matišić
 * PROJECT: Termi-Linux version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Geo calculator main file
*/

#include <iostream>
#include <fstream>

using namespace std;

#define MAX 1000

#include "Calc.h"

int main()
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
    {
    
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
                /* wrong command */
                else
                {
                    
                }

            }

        }
    }
    return 0;
}