#pragma once

/* include */
#include <iostream>
#include <map>

/* commands */
std::string test_command;
std::string opengl_command;
std::string lua_command;

/* database */
std::map<std::string, std::string> database = 
{
    {"test", test_command,},
    {"OpenGL", opengl_command},
    {"Termi-Lua", lua_command}
};
