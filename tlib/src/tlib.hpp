/**
 * @author Andrej Bartulin
 * PROJECT: tlib = Lesper
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main header file for tlib
 */

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>
#include <vector>

#include "util.hpp"

static std::vector<std::string> tokens;
static std::vector<std::string> num_stack;
static std::vector<std::string> numbers = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
static std::vector<std::string> operators = {"+", "-", "*", "/", "%"};
static std::vector<std::string> parentheses = {"(", ")"};

static std::map<std::string, std::string> symbols;

struct keywords
{
    std::string print = "PRINT";
    std::string input = "INPUT";
    std::string if_key = "IF";
    std::string endif = "ENDIF";
    std::string then = "THEN";
    std::string variable = "$";
};

struct errors
{
    std::string undefined_variable = "Undefined variable!";
    std::string wrong_file_extension = "Wrong file extension! Expected *.lesper!";
};

std::string open_file(std::string filename);
int lex(std::string filecontents, struct keywords *k);
float evalExpression(std::string expr);
void print(std::string str);
void assign(std::string varname, std::string varvalue);
std::string get_variables(std::string varname, struct errors *error);
void input(std::string str, std::string varname);
void parse(struct errors *error);
void run(std::string path);
