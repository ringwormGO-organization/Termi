/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Export stuff
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#if API_EXPORT
#define _API __declspec(dllexport)
#else
#define _API __declspec(dllimport)
#endif

extern "C"
{
	__declspec(dllexport) void __cdecl base64(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl calc(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl cd(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl change_setting(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl echo(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl find_command(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl geocalc(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl list_dir(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl new_dir(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl openfile(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl ping(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl rm(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl sysfetch(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl ttime(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl whoami(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl writefile(const std::vector<std::string>& vect);
	__declspec(dllexport) void __cdecl yes(const std::vector<std::string>& vect);
};
