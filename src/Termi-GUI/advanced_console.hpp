/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Header file for advanced console model
 */

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "imgui_code.hpp"

/*
 * Class handling advanced console model.
 * This console model SUPPORTS interaction with executing process.
 */
class AdvancedConsole : public ConsoleBase
{
    public:
        AdvancedConsole(/* args */);
        ~AdvancedConsole();

    public:
        /**
         * `printf()` for our console
         * @param fmt string
        */
        void AddLog(const char *fmt, ...) override;

        /**
         * Draw the console
        */
        void Draw() override;
};
