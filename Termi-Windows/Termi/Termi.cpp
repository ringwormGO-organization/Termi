#include "Termi.h"
#include <iostream>
#include <string>

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

extern void Terminal() {
    std::cout << "Welcome to Termi!! (C) 2021 ringwormGO\nType command..." << std::endl;

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
        else
        {
            std::cout << "Command invalid" << std::endl;
        }
    }
}