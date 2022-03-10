#pragma once

#include <iostream>

unsigned int state = 0;

std::string arg1;
std::string arg2;
std::string arg3;

void removeDupWord(std::string str)
{
    std::string word = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            state++;

            switch (state)
            {
                case 1:
                    arg1 = word;
                    break;

                case 2:
                    arg2 = word;
                    break;

                case 3:
                    arg3 = word;
                    break;

                default:
                    break;
            }
 
            word = "";
        }
        else 
        {
            word = word + x;
        }
    }

    switch (state)
    {
        case 1:
            arg1 = word;
            break;

        case 2:
            arg2 = word;
            break;

        case 3:
            arg3 = word;
            break;

        default:
            break;
    }
}
