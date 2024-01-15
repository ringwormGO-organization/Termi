/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Export stuff
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#if defined _WIN32 || defined _WIN64
	#define EXPORT __declspec(dllexport) void __cdecl
	#define EXPORT_AUTO __declspec(dllexport) auto __cdecl
#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
        defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
	#define EXPORT void
	#define EXPORT_AUTO auto
#endif

extern "C"
{
	EXPORT base64(const std::vector<std::string>& vect);
	EXPORT calc(const std::vector<std::string>& vect);
	EXPORT cd(const std::vector<std::string>& vect);
	EXPORT change_setting(const std::vector<std::string>& vect);
	EXPORT dencalc(const std::vector<std::string>& vect);
	EXPORT echo(const std::vector<std::string>& vect);
	EXPORT find_command(const std::vector<std::string>& vect);
	EXPORT geocalc(const std::vector<std::string>& vect);
	EXPORT list_dir(const std::vector<std::string>& vect);
	EXPORT new_dir(const std::vector<std::string>& vect);
	EXPORT openfile(const std::vector<std::string>& vect);
	EXPORT rm(const std::vector<std::string>& vect);
	EXPORT sysfetch(const std::vector<std::string>& vect);
	EXPORT ttime(const std::vector<std::string>& vect);
	EXPORT whoami(const std::vector<std::string>& vect);
	EXPORT writefile(const std::vector<std::string>& vect);
	EXPORT_AUTO yes(const std::vector<std::string>& vect) -> void;
};
