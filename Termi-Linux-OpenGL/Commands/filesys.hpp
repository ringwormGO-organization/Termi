/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Filesystem heder file
*/

#pragma once

#include <dirent.h>

int openfile(std::string file, std::string argument);
int list(std::string argument, std::string argument2);
int writefile(std::string file, std::string content);
int new_dir(std::string folder, std::string argument);
int cd(std::string folder, std::string argument);
int rm(std::string folder, std::string argument);
