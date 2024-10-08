/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Header file for Dear ImGui code
 */

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "font.inl"

#include "server.hpp"
#include "settings.hpp"
#include "translation.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <mutex>
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

/* All global variables which we need */
static float pos_x = 0;
static float pos_y = 0;
static float window_width = 650;
static float window_height = 650;

static bool alReadyPrinted = false;

/**
 * Commands map
 * @param first name
 * @param second function name in Termi-Commands
 */
static std::map<const std::string, const std::string> commands =
    {
        {"base64", "base64"},
        {"calc", "calc"},
        {"cd", "cd"},
        {"dencalc", "dencalc"},
        {"echo", "echo"},
        {"find", "find_command"},
        {"geocalc", "geocalc"},
        {"list", "list_dir"},
        {"mkdir", "new_dir"},
        {"openfile", "openfile"},
        {"rm", "rm"},
        {"sysfetch", "sysfetch"},
        {"time", "ttime"},
        {"whoami", "whoami"},
        {"writefile", "writefile"},
        {"yes", "yes"}};

/**
 * Check if the string starts with substring
 * @param fullString - string
 * @param starting - substring
 */
static bool isStarting(std::string const &fullString, std::string const &starting)
{
    if (fullString.length() <= starting.length())
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

/**
 * Function to calculate whitespaces
 * Credits: https://www.geeksforgeeks.org/isspace-in-c-and-its-application-to-count-whitespace-characters/
 * @param str - string
 */
static int whitespaces(std::string &str)
{
    int count = 0;
    int length = str.length();

    for (int i = 0; i < length; i++)
    {
        int c = str[i];
        if (isspace(c))
            count++;
    }

    return count;
};

/**
 * Colorize text
 * Credits: https://github.com/ocornut/imgui/issues/902#issuecomment-1103072284
 * @param text - string to colorize
 * @param colors - std::pair of letter representing color and ImVec4 representing color values in 4D vector
 */
void ColorfulText(const std::string &text, const std::list<std::pair<char, ImVec4>> &colors);

static const ImVec4 &
    white = {1, 1, 1, 1},
    blue = {0.000f, 0.703f, 0.917f, 1},
    red = {0.976f, 0.117f, 0.265f, 1},
    grey = {0.230f, 0.226f, 0.289f, 1},
    lgrey = {0.630f, 0.626f, 0.689f, 1},
    green = {0.5f, 1.0f, 0.5f, 1.0f},
    lime = {0.55f, 0.90f, 0.06f, 1},
    yellow = {0.91f, 1.00f, 0.21f, 1},
    purple = {1, 0, 1, 1},
    orange = {1.00f, 0.36f, 0.09f, 1};

/**
 * Split given string using the getline() function
 * Credits: https://www.javatpoint.com/how-to-split-strings-in-cpp
 * @param str - string
 * @param delim - separator
 * @param out - output vector
 */
void split_str(std::string const &str, const char delim, std::vector<std::string> &out);

/**
 * Class containing runtime GUI settings
 * This GUI model is simple and does not support sending interaction with executing process
 */
class SimpleVars
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
 * Class containing implementation of GUI model 0
 * This GUI model is simple and does not support sending interaction with executing process
 */
class SimpleGUI : public SimpleVars
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

/*
    * Class handling console
    * This GUI model is simple and does not support sending interaction with executing process
    * Code from imgui_demo.cpp
    */
class SimpleConsole : public SimpleGUI
{
    protected:
        char InputBuf[256];
        ImVector<char *> Items;
        ImVector<const char *> Commands;
        ImVector<char *> History;
        int HistoryPos; // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter Filter;
        bool AutoScroll;
        bool ScrollToBottom;
        bool Copy;
        char *s;

    public:
        SimpleConsole();
        ~SimpleConsole();

    protected:
        // Portable helpers
        static int Stricmp(const char *s1, const char *s2)
        {
            int d;
            while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
            {
                s1++;
                s2++;
            }
            return d;
        };
        static int Strnicmp(const char *s1, const char *s2, int n)
        {
            int d = 0;
            while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1)
            {
                s1++;
                s2++;
                n--;
            }
            return d;
        };
        static char *Strdup(const char *s)
        {
            IM_ASSERT(s);
            size_t len = strlen(s) + 1;
            void *buf = malloc(len);
            IM_ASSERT(buf);
            return (char *)memcpy(buf, (const void *)s, len);
        };
        static void Strtrim(char *s)
        {
            char *str_end = s + strlen(s);
            while (str_end > s && str_end[-1] == ' ')
                str_end--;
            *str_end = 0;
        };

    public:

        /**
         * Load function from dynamic library
         * @param path path to the .so/.dll file
         * @param function name of function
         * @param argument function's argument
        */
        template <typename T>
        int LoadDynamicLibrary(const char* path, const char* function, T argument);

    public:

        /**
         * Clear entire console, but print `Termi >`
        */
        void ClearLog();

        /**
         * Same as `ClearLog()`, but don't print `Termi >`
        */
        void FullClearLog();

        /**
         * `printf()` for our console
         * @param fmt string
        */
        void AddLog(const char *fmt, ...);

        /**
         * Draw the console
        */
        void Draw();

        /**
         * Execute a command
         * @param command_line user's input
        */
        void ExecCommand(std::string command_line, ...);

        /**
         * Print `Termi >`
        */
        void TypeTermi();

    protected:
        // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
        static int TextEditCallbackStub(ImGuiInputTextCallbackData *data)
        {
            SimpleConsole *con = (SimpleConsole *)data->UserData;
            return con->TextEditCallback(data);
        }

        int TextEditCallback(ImGuiInputTextCallbackData *data);
};

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

extern SimpleConsole console;

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
