/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Settings class header file
*/

#pragma once

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

#include <string.h>

#if defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
#include <unistd.h>
#endif

#include <json-c/json.h>

/* Settings class */
class Settings
{
public:
	Settings();
	~Settings();

	std::string GetStartupCommand();
	int GetWidth();
	int GetHeight();
	std::string GetFontName();
	int GetFontSize();
	std::string GetGlyphRange();
	int GetConsoleModel();
	int GetPort();

private:
	void CreateFile();
	std::string path;
};
