/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Header file for GUI code
 */

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "utils/font.inl"

#include "network/server.hpp"
#include "utils/settings.hpp"
#include "utils/translation.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
    #include <direct.h>

    #define PATH_MAX        4096    /* # chars in a path name including nul */
    #define _API __declspec(dllexport)

    #define COMMANDS_PATH "Termi-Commands.dll"
#elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
    defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
    #include <sys/stat.h>
    #include <unistd.h>
    #include <limits.h>
    #include <dlfcn.h>

    #define _API

    #define COMMANDS_PATH "libTermi-Commands.so"
#endif

#include <stddef.h>

#include <json-c/json.h>

/* ------------------------------------------------------------------------- */

/* All global variables which we need */
static float pos_x = 0;
static float pos_y = 0;
static float window_width = 650;
static float window_height = 650;

static bool alReadyPrinted = false;

/* ------------------------------------------------------------------------- */

/**
 * Class containing runtime GUI settings.
 */
class Vars
{
    public:
        std::string language = "English";
        std::string theme = "none";

        std::vector<std::string> themes = {"dark_red", "aqua", "some_yellow"};

        bool isDarkTheme = false;
        bool language_dialog = false;
        bool termi_dialog = false;
        bool imgui_dialog = false;
        bool settings_dialog = false;
        bool alReadyFocusOnInputBar = false;

        bool server = false; 
};

/**
 * Class containing GUI implementation.
 */
class GUI : public Vars
{
    public:

        /**
         * Draw a top menu
         * @param style
        */
        void DrawMenu(ImGuiStyle& style);

        /**
         * Return English text or its translated counterpart
         * @param text some text
        */
        std::string ChooseLanguage(std::string text);

        /**
         * Dialog for choosing a language
         * @param p_open is dialog open?
        */
        void ChooseLanguageDialog(bool *p_open);

        /**
         * Dialog showing informations about Termi
         * @param p_open is dialog open?
        */
        void TermiDialog(bool *p_open);

        /**
         * Dialog showing informations about ImGui
         * @param p_open is dialog open?
        */
        void ImGuiDialog(bool *p_open);
};

/**
 * Class containing basic functions which all console models need to have.
 */
class ConsoleBase : public GUI
{
    public:
        ConsoleBase();
        virtual ~ConsoleBase();

    public:
        /**
         * `printf()` for our console
         * @param fmt string
         * 
         * NOTE: Even though, it's not needed for console model 2, it has to be here
         * so it is accessible from `vrenderer` for "extern C" purposes.
        */
        virtual void AddLog(const char *fmt, ...);

        /**
         * Draw the console
        */
        virtual void Draw();
};

/* ------------------------------------------------------------------------- */

/**
 * Draw tabs
 * @param style 
*/
void DrawTab(ImGuiStyle& style);

/**
 * Entry point for ImGui part of Termi
 * @param style
*/
void main_code(ImGuiStyle& style);

extern "C"
{
    /**
     * Entry point for whole Termi-GUI project
    */
    _API void tmain();

    /**
     * AddLog but outside the so it is visible from .so/.dll files
     * @param fmt - string
     */
    _API void AddLog(const char *fmt, ...);
};
