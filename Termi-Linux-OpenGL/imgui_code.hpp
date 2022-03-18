/**
 * @author Andrej Bartulin
 * @mainteiner Stjepan Bilić Matišić
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

#include <iostream>
#include <fstream>

/* All variables which is required */
static float pos_x = 0;
static float pos_y = 0;
static float window_width = 900;
static float window_height = 900;

static bool isDarkTheme = false;

static bool alReadyPrinted;

class Renderer
{
    public:
        void DrawContextMenu();
        void Console();

    private:
        void DrawNewTab();
        void Color();
        void Font();
};

void main_code();

extern Renderer* render;
