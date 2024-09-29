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
#include <unistd.h>

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
	int GetGuiModel();
	int GetPort();

private:
	void CreateFile();
	std::string path;
};
