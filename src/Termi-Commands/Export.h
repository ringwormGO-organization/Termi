/**
 * @author Andrej Bartulin
 * PROJECT: Termi version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Export stuff
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
	extern "C"
	{
		__declspec(dllexport) void __cdecl base64(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl calc(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl cd(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl change_setting(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl dencalc(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl echo(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl find_command(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl geocalc(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl list_dir(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl new_dir(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl openfile(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl rm(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl sysfetch(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl ttime(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl whoami(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl writefile(const std::vector<std::string>& vect);
		__declspec(dllexport) auto __cdecl yes(const std::vector<std::string>& vect) -> void;
	};
#elif _WIN64
	extern "C"
	{
		__declspec(dllexport) void __cdecl base64(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl calc(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl cd(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl change_setting(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl dencalc(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl echo(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl find_command(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl geocalc(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl list_dir(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl new_dir(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl openfile(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl rm(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl sysfetch(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl ttime(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl whoami(const std::vector<std::string>& vect);
		__declspec(dllexport) void __cdecl writefile(const std::vector<std::string>& vect);
		__declspec(dllexport) auto __cdecl yes(const std::vector<std::string>& vect) -> void;
	};
#elif __APPLE__ || __MACH__
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
#elif __linux__
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
#elif __FreeBSD__
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
#endif
