/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Header file for Dear ImGui code
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Settings.hpp"
#include "Translation.hpp"

#include "Commands/base64.hpp"
#include "Commands/Neofetch.hpp"
#include "Commands/filesys.hpp"
#include "Commands/calc.hpp"
#include "Commands/other.hpp"
#include "Commands/time.hpp"
#include "Commands/termi.hpp"

#include "Commands/Geocalc.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <functional>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

/* All variables which are required */
static float pos_x = 0;
static float pos_y = 0;
static float window_width = 650;
static float window_height = 650;

static bool isDarkTheme = false;
static bool isFont = false;
static bool font_change = false;
static bool language_dialog = false;
static bool isDemoWindow = false;
static bool termi_dialog = false;
static bool imgui_dialog = false;
static bool settings_dialog = false;

static bool alReadyPrinted = false;
static bool help_focus = false;

static const char* language;

/* 
 * Commands list - command and function
 * name of command, name of function
*/
static std::map<const std::string, const std::function<int(std::vector<std::string>& vect)>> commands = 
{
    {"base64", base64},
    {"calc", calc},
    {"cd", cd},
    {"change-setting", change_setting},
    {"echo", echo},
    {"find", find_command},
    {"geocalc", geocalc},
    {"list", list_dir},
    {"mkdir", new_dir},
    {"neofetch", neofetch},
    {"openfile", openfile},
    {"time", ttime},
    {"rm", rm},
    {"whoami", whoami},
    {"writefile", writefile},
    {"yes", yes}
};

static std::map<const std::string, const std::string> cmbal = 
{
    {"writeln", "Cmbal/examples/writeln.cmbal"}
};

/* Check if some string start with some std::string value */
static bool isStarting (std::string const &fullString, std::string const &starting) 
{
    if (fullString.length() <= starting.length()) { return true; }
    else { return false; }
}

/* 
 * Function to calculate whitespaces
 * Credits: https://www.geeksforgeeks.org/isspace-in-c-and-its-application-to-count-whitespace-characters/ 
 */
static int whitespaces(std::string& str)
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

/* 
 * Function which colors text
 * Credits: https://github.com/ocornut/imgui/issues/902#issuecomment-1103072284
*/
void ColorfulText(const std::string& text, const std::list<std::pair<char, ImVec4>>& colors = {});

static const ImVec4&
white = { 1,1,1,1 },
blue = { 0.000f, 0.703f, 0.917f,1 },
red = { 0.976f, 0.117f, 0.265f ,1 },
grey = { 0.230f, 0.226f, 0.289f,1 },
lgrey = { 0.630f, 0.626f, 0.689f,1 },
green = {0.5f, 1.0f, 0.5f, 1.0f},
lime = { 0.55f, 0.90f, 0.06f,1 },
yellow = { 0.91f, 1.00f, 0.21f,1 },
purple = { 1,0,1,1 },
orange = { 1.00f, 0.36f, 0.09f,1 };

/* 
 * Function to split the given string using the getline() function
 * Credits: https://www.javatpoint.com/how-to-split-strings-in-cpp
*/
void split_str(std::string const &str, const char delim, std::vector <std::string> &out);

/*
 * Console class - everything for drawing and managing console
 * Code from imgui_demo.cpp
*/
class Console
{
    protected:
        char                  InputBuf[256];
        ImVector<char*>       Items;
        ImVector<const char*> Commands;
        ImVector<char*>       History;
        int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
        ImGuiTextFilter       Filter;
        bool                  AutoScroll;
        bool                  ScrollToBottom;
        bool                  Copy;
        char*                 s;

    public:
        Console();
        ~Console();

    protected:
        // Portable helpers
        static int   Stricmp(const char* s1, const char* s2) { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; };
        static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; };
        static char* Strdup(const char* s) { IM_ASSERT(s); size_t len = strlen(s) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)s, len); };
        static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; };

    public:
        void ClearLog();
        void FullClearLog();
        void AddLog(const char* fmt, ...);
        void Draw();
        void ExecCommand(std::string command_line, ...);
        void TypeTermi();

    protected:
        // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
        static int TextEditCallbackStub(ImGuiInputTextCallbackData* data)
        {
            Console* con = (Console*)data->UserData;
            return con->TextEditCallback(data);
        }

        int TextEditCallback(ImGuiInputTextCallbackData* data);
};

/* Renderer class */
class Renderer
{
    public:
        void DrawTab();
        void Font(bool* p_open);

        const char* ChooseLanguage(const char* word);
        void ChooseLanguageDialog(bool* p_open);

        void TermiDialog(bool* p_open);
        void ImGuiDialog(bool* p_open);

        float Settings(int id, float value);

        bool CheckFile(const char* name);

        std::string font_name;
        std::string startup_command;

    private:
        void DrawMenu();
};

/* Main code for starting ImGui */
void main_code();

extern Console console;
extern Renderer render;