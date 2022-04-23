/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Filesystem heder file
*/

#pragma once

#include <dirent.h>

void openfile(std::string file, std::string argument);
void list(std::string argument, std::string argument2);
void writefile(std::string file, std::string content);
void new_dir(std::string folder, std::string argument);
void cd(std::string folder, std::string argument);
void rm(std::string folder, std::string argument);
