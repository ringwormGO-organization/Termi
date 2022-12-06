/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Export stuff
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

extern "C"
{
	void base64(const std::vector<std::string>& vect);
	void calc(const std::vector<std::string>& vect);
	void cd(const std::vector<std::string>& vect);
	void change_setting(const std::vector<std::string>& vect);
	void dencalc(const std::vector<std::string>& vect);
	void echo(const std::vector<std::string>& vect);
	void find_command(const std::vector<std::string>& vect);
	void geocalc(const std::vector<std::string>& vect);
	void list_dir(const std::vector<std::string>& vect);
	void new_dir(const std::vector<std::string>& vect);
	void openfile(const std::vector<std::string>& vect);
	void rm(const std::vector<std::string>& vect);
	void sysfetch(const std::vector<std::string>& vect);
	void ttime(const std::vector<std::string>& vect);
	void whoami(const std::vector<std::string>& vect);
	void writefile(const std::vector<std::string>& vect);
	auto yes(const std::vector<std::string>& vect) -> void;
};
