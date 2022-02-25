#include "main.h"
#include "Commands.h"
#include "Calc.h"

std::string help = "help";
std::string opencalc = "opencalc";
std::string geocalc = "geocalc";
std::string custset = "custset";
std::string filesys = "filesys";

void Help()
{
    using namespace std;

    cout << "help - shows list of commands" << endl;
    cout << "opencalc - opens a calculator" << endl;
    cout << "geocalc - opens a geometric calculator" << endl;
    cout << "filesys - opens file creation/editing" << endl;
    cout << "filesys / openfile - opens a file" << endl;
    cout << "filesys / writefile - create and edit a file" << endl;
}

void Filesys()
{
    using namespace std;

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
        if (!my_file) 
        {
            cout << "No such file" << endl;
        }

        else 
        {
            char ch;

            while (1) 
            {
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

    else
    {
        cout << "ERROR >> COMMAND NOT FOUND" << endl;
    }
}

void OpenCalc()
{
    using namespace std;

    char op;
    float num1, num2;

    cout << "Enter operator: +, -, *, /: ";
    cin >> op;

    cout << "Enter the first number: ";
    cin >> num1;
    cout << "Enter the second number: ";
    cin >> num2;

    switch(op) 
    {

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

void GeoCalc()
{
    using namespace std;

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

            }
        }
    }
}