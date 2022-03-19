/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Header file for ImGUI code
 * INFORAMTION: Compile solution, else check Victor Gordan's video
*/

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Settings.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

/* All variables which is required */
static float pos_x = 0;
static float pos_y = 0;
static float window_width = 900;
static float window_height = 900;

static bool isDarkTheme = false;
static bool isFont = false;
static bool isDemoWindow = false;

static bool alReadyPrinted;

/* Commands - command and path */
static std::map<std::string, std::string> commands = 
{
    {"Termi", "../Termi-Linux/Termi"}
};

/* Renderer class */
class Renderer
{
    public:
        void DrawContextMenu();
        void Font();

    private:
        void DrawNewTab();
};

/* Main code for starting ImGui */
void main_code();

extern Renderer* render;
