/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Project's main header file
*/

#pragma once

#include <string>
#include <vector>

#if defined _WIN32 || defined _WIN64
	#define GUI_PATH "Termi-GUI.dll"

	/**
	 * Load a function from .so file, aka dynamic library
	 * @param path path to the file
	 * @param function function name
	 * @param value function's argument
	 */
	template <typename T>
	int LoadDynamicLibrary(const char* path, const char* function, T value);

	/*
	* Return version of Windows operating system
	* Helper function to Windows' version of `sysfetch` command
	*/
	const char* OperatingSystem();

	/**
	 * Return uptime time in seconds 
	 * Helper function to Windows' version of `sysfetch` command
	 */
	uint64_t UptimeS();

	/**
	 * Return uptime time in minutes
	 * Helper function to Windows' version of `sysfetch` command
	 */
	uint64_t UptimeM();

	/**
	 * Return uptime time in hours
	 * Helper function to Windows' version of `sysfetch` command
	 */
	uint64_t UptimeH();

#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
	#define GUI_PATH "libTermi-GUI.so"

	/**
	 * Load a function from .so file, aka dynamic library 
	 * @param path path to the file
	 * @param function function name
	 * @param value function's argument
	 */
    template <typename T>
    int LoadDynamicLibrary(const char* path, const char* function, T value);
#endif

/**
 * `printf()` for our commands
 * Calls `AddLog()` from Termi-GUI
 * @param fmt sequence of text to be printed
 */
void AddLog(std::string fmt, ...);

/**
 * Print status message
 * @param error_code error code
 */
void Status(int error_code);

/* -------------------------------------------------------- */

#if defined _WIN32 || defined _WIN64
	#define EXPORT __declspec(dllexport) void __cdecl
	#define EXPORT_AUTO __declspec(dllexport) auto __cdecl
#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
        defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
	#define EXPORT void
	#define EXPORT_AUTO auto
#endif

/**
 * Export core commands
 */
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
