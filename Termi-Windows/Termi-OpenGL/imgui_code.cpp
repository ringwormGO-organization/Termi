/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Windows version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file for ImGUI
 * INFORAMTION: Compile this Visual Studio solution
*/

#include "imgui_code.hpp"

using namespace std;

Status status;

ContextMenu* contextmenu;

/* Code for ContextMenu class */

/* PRIVATE INSTANCES OF ContextMenu class */

/* Draw new teminal tab */
void ContextMenu::DrawNewTab()
{
    
}

/* Draw context menu */
void ContextMenu::DrawContextMenu()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("New terminal tab", "Ctrl+N"))
        {

        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit", "Ctrl+W"))
        {
            exit(0);
        }

        ImGui::Separator();

        if (ImGui::MenuItem("Nothing"))
        {
            /* do nothing */
        }

        ImGui::EndMenu();
    }
}

void main_code()
{
    /* ImGUI window creation */
    ImGui::SetNextWindowPos(ImVec2((float)0, (float)0));
    ImGui::SetNextWindowSize(ImVec2((float)900, (float)900));
    ImGui::Begin("Termi", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);

    #ifdef PRINT_WHEN_WINDOW_IS_CREATED
        if (!status.alReadyPrinted)
        {
            std::cout << "ImGUI window is created.\n";
            status.alReadyPrinted = true;
        }

        if (status.alReadyPrinted)
            /* do nothing */
    #endif

    contextmenu->DrawContextMenu();
        
    /* End of window */
    ImGui::End();
}
