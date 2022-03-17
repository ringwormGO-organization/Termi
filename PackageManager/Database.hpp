/**
 * @author: Andrej Bartulin
 * PROJECT: Termi Package Manager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Database
 * 
*/

#pragma once

/* include */
#include <iostream>
#include <map>

/* commands */
std::string test_command = "echo Hello";
std::string opengl_link = "https://github.com/ringwormGO-organization/Termi/raw/main/Termi-Linux-OpenGL/Termi-OpenGL";
std::string lua_command;

/* database */
std::map<std::string, std::string> database = 
{
    {"test", test_command,},
    {"OpenGL", opengl_link},
    {"Termi-Lua", lua_command}
};
