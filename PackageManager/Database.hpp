#pragma once

/* include */
#include <iostream>
#include <map>

/* commands */
std::string termi_command;

/* database */
std::map<std::string, std::string> database = 
{
    {"Termi", termi_command,},
    {"Rust", "curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh",}
};
