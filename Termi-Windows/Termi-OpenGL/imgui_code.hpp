/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Header file for ImGUI code
 * INFORAMTION: ICompile solution, else check Victor Gordan's video
*/

#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Settings.hpp"
#include "Translation.hpp"

#include "Commands/Neofetch.hpp"
#include "Commands/filesys.hpp"
#include "Commands/calc.hpp"
#include "Commands/other.hpp"
#include "Commands/time.hpp"

#include <iostream>
#include <functional>
#include <fstream>
#include <map>
#include <string>
#include <ctime>
#include <chrono>

#include <Windows.h>
#include <direct.h>
#include "dirent.h"
#include "limits.h"

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

static char font_name[250];

/* 
 * Commands list - command and function
 * name of command, name of function
*/
static std::map<const std::string, const std::function<int(const std::string, const std::string)>> commands = 
{
    {"cd", cd},
    {"echo", echo},
    {"list", list},
    {"mkdir", new_dir},
    {"neofetch", neofetch},
    {"openfile", openfile},
    {"time", ttime},
    {"rm", rm},
    {"writefile", writefile},
    {"yes", yes}
};

/* Check if some string start with some std::string value */
static int isStarting (std::string const &fullString, std::string const &starting) 
{
    if (fullString.length() <= starting.length()) { return 0; }
    else { return 1; }
}

/*
 * Console class - everything for drawing and managing console
 * Setting up functions here
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

        int Settings(int id);
        void SettingsDialog(bool* p_open);

        int CheckFile(const char* name);

    private:
        void DrawMenu();
};

/* Main code for starting ImGui */
void main_code();

extern Console console;
extern Renderer* render;
