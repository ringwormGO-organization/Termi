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

struct Canvas
{
    int width;
    int height;
};

struct Status
{
	bool alReadyPrinted;
};


void Print();

void main_code();
