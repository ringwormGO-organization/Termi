/**
 * @author Andrej Bartulin
 * @mainteiner Stjepan Bilić Matišić
 * PROJECT: Termi-Linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file for ImGUI
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui_code.hpp"

using namespace std;

Renderer* render;

/* Code for Renderer class */
/* PRIVATE INSTANCES OF Renderer class */

/* Draw new teminal tab */
void Renderer::DrawNewTab()
{
    
}

void Renderer::Color()
{

}

void Renderer::Font()
{
    
}

/* Draw context menu */
void Renderer::DrawContextMenu()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New terminal tab", "Ctrl+N"))
            {
                
            }

            if (ImGui::MenuItem("New terminal profile", "Ctrl+Shift+N"))
            {
                
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Exit", "Ctrl+W"))
            {
                exit(0);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Color picker"))
            {
                Color();
            }

            if (ImGui::MenuItem("Font picker"))
            {
                Font();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Change theme", "Ctrl+T"))
            {
                cout << "In progress!\n\n";
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

/* Terminal/console part */
void Renderer::Console()
{

}

void main_code()
{
    /* ImGUI window creation */
    ImGui::SetNextWindowPos(ImVec2(pos_x, pos_y));
    ImGui::SetNextWindowSize(ImVec2(window_width, window_height));
    ImGui::Begin
    (  "Termi", 
        NULL, 
        ImGuiWindowFlags_NoMove  | 
        ImGuiWindowFlags_NoCollapse | 
        ImGuiWindowFlags_AlwaysAutoResize | 
        ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_MenuBar
    );

    #ifdef PRINT_WHEN_WINDOW_IS_CREATED
        if (!alReadyPrinted)
        {
            std::cout << "ImGUI window is created.\n";
            alReadyPrinted = true;
        }

        if (alReadyPrinted)
            /* do nothing */
    #endif

    render->DrawContextMenu();
    render->Console();
        
    /* End of window */
    ImGui::End();
}
