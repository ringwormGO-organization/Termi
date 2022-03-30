/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Header file for ImGUI code
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Settings.hpp"
#include "Translation.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <string>

/* All variables which is required */
static float pos_x = 0;
static float pos_y = 0;
static float window_width = 900;
static float window_height = 900;

static bool isDarkTheme = false;
static bool isFont = false;
static bool language_dialog = false;
static bool isDemoWindow = false;

static bool alReadyPrinted;

static const char* language;

/* Commands list - command and path */
static std::map<const std::string, const std::string> commands = 
{
    {"test", "test"}
};

/* Renderer class */
class Renderer
{
    public:
        void DrawContextMenu();
        void Font(bool* p_open);

        
        const char* ChooseLanguage(const char* word);
        void ChooseLanguageDialog(bool* p_open);

    private:
        void DrawNewTab();
        int CheckFile(char name[200]);
};

/* Main code for starting ImGui */
void main_code();

extern Renderer* render;
