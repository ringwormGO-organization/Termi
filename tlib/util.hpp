/**
 * @author Andrej Bartulin
 * PROJECT: tlib = Lesper
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Header file for utils
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

class Eval
{
    public:
        Eval(std::string expr, std::vector<std::string> parentheses, std::vector<std::string> numbers);
        ~Eval();

        float ret;
        bool error_state = false;

    private:
        float Parentheses(std::string expr, std::vector<std::string> numbers);
        float Operators(std::string expr, std::vector<std::string> numbers);
        float Numbers(std::string expr, std::vector<std::string> numbers);
};

std::string lower(std::string str);
bool containsSomething(std::string str, std::vector<std::string> vec);
bool containsSpecificOperators(std::string str, int id);
bool evaluateTokens(std::vector<std::string> tokens, int i, std::string str, int substr, int option);
bool compare(std::string str, std::string str2);
