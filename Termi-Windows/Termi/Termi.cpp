#include <iostream>
#include <stdlib.h>
#include <string>
#include "windows.h"

#include "Termi.h"
#include "Header.h"

extern int Add(int a, int b) {
    return a + b;
}

extern int Minus(int a, int b) {
    return a - b;
}

void Floppy() {
    std::cout <<"%%%%&&&&..............%%%/  " << std::endl << 
                "%%%%&&&&.........&&&..%%%%%   " << std::endl << 
                "%%%%&&&&.........&&&..%%%%%%%" << std::endl << 
                "%%%%&&&&.........&&&..%%%%%%% " << std::endl <<
                "%%%%&&&&.........&&&..%%%%%%% " << std::endl <<
                "%%%%&&&&.........,,,..%%%%%%%" << std::endl <<
                "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << std::endl <<
                "%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << std::endl <<
                "%%%%  _________________ .%%%%" << std::endl <<
                "%%%%  _________________ .%%%%" << std::endl <<
                "%%%%  _________________ .%%%%" << std::endl <<
                "%%%%  _________________ .%%%%" << std::endl <<
                "%%%%  _________________ .%%%%" << std::endl <<
                "%%%%  _________________ .%%%%" << std::endl <<
                "%&&%                    ,%&&%" << std::endl <<
                "%&&%%%%%%%%%%%%%%%%%%%%%%%&&%" << std::endl <<
                "%&&%%%%%%%%%%%%%%%%%%%%%%%&&%" << std::endl;
}
void Calculator() {
    std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "Enter an operator (subt = subtraction | add = addition | dev = devision | mul = multiplication)" << std::endl;
    std::cout << "Type ex to exit calculator" << std::endl;
    std::cout << " " << std::endl;
    std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;
    while (1)
    {
        std::cout << "calc > ";
        std::string inpOPR;
        std::cin >> inpOPR;
        std::string subt = "subt";
        std::string add = "add";
        std::string dev = "dev";
        std::string mul = "mul";
        std::string ex = "ex";


        if (inpOPR == subt)
        {
            double x, y;
            double res;
            std::cout << "Type a number: ";
            std::cin >> x;
            std::cout << "Type a  second number: ";
            std::cin >> y;
            std::cout << "Result: "
                << subOfTwoNumbers(x, y)
                << std::endl;

        }

        else if (inpOPR == add)
        {
            double x, y;
            double res;
            std::cout << "Type a number: ";
            std::cin >> x;
            std::cout << "Type a second number: ";
            std::cin >> y;
            std::cout << "Result: "
                << sumOfTwoNumbers(x, y)
                << std::endl;

        }

        else if (inpOPR == mul)
        {
            double x, y;
            double res;
            std::cout << "Type a number: ";
            std::cin >> x;
            std::cout << "Type a second number: ";
            std::cin >> y;
            std::cout << "Result: "
                << mulOfTwoNumbers(x, y)
                << std::endl;

        }

        else if (inpOPR == dev)
        {
            double x, y;
            double res;
            std::cout << "Type a number: ";
            std::cin >> x;
            std::cout << "Type a second number: ";
            std::cin >> y;
            std::cout << "Result: "
                << devOfTwoNumbers(x, y)
                << std::endl;

        }

        else if (inpOPR == ex)
        {
            break;
        }
        else
        {
            std::cout << "ERROR = COMMAND NOT CORRECT / IT DOSENT EXIST" << std::endl;
        }
    }
}

extern void Terminal() {
    std::cout << "Welcome to Termi!! (C) 2021 ringwormGO\nType command..." << std::endl;
    std::cout << "ooooooooooo ooooooooooo                          o88   " << std::endl;
    std::cout << "88  888  88  888    88  oo oooooo  oo ooo oooo   oooo  " << std::endl;
    std::cout << "    888      888ooo8     888    888 888 888 888   888 " << std::endl;
    std::cout << "    888      888    oo   888        888 888 888   888  " << std::endl;
    std::cout << "   o888o    o888ooo8888 o888o      o888o888o888o o888o " << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;


    while (true)
    {
        std::cout << "Termi> ";

        std::string command;
        std::cin >> command;


        if (command == "help")
        {
            std::cout << "Help" << std::endl;
        }
        else if (command == "floppy")
        {
            Floppy();
        }
        else if (command == "exit")
        {
            exit(0);
        }
        else if (command == "calculator")
        {
            Calculator();
        }
        else
        {
            std::cout << "Command invalid" << std::endl;
        }
    }
}