/**
 * @author(S):
        original: StjepanBM1
        OpenGL: Andrej Bartulin
 * PROJECT: Termi-Windows version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Filesystem header file
*/

#pragma once

#include <iostream>

int openfile(std::string file, std::string argument);
int list(std::string argument, std::string argument2);
int writefile(std::string file, std::string content);
int new_dir(std::string folder, std::string argument);
int cd(std::string folder, std::string argument);
int rm(std::string folder, std::string argument);
