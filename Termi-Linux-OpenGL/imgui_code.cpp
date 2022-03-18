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

            if (ImGui::MenuItem("Font picker", "Ctrl+F"))
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

        if (ImGui::BeginMenu("Help"))
        {

            if (ImGui::MenuItem("About ImGUI", "Ctrl+A"))
            {
                ImGui::ShowDemoWindow();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("About Termi", "Ctrl+Shift+A"))
            {
                
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

/* Terminal/console part */
void Renderer::Console()
{
    ImGuiIO& io1 = ImGui::GetIO(); (void)io1;

    static char text[4096] = "Termi> ";

    ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(window_width, window_height - 100), ImGuiInputTextFlags_EnterReturnsTrue);
}

void Renderer::Font()
{
    if (isFont == true)
        isFont = false;
    else
        isFont == true;
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
        ImGuiWindowFlags_MenuBar |
        ImGuiInputTextFlags_AllowTabInput
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

    #ifdef PRINT_FPS
        ImGui::SetCursorPosX(window_width + window_width / 200 - 100);
        ImGui::TextColored(ImVec4(0, 0.88f, 0.73f, 1.00f), "(%.1f FPS)", ImGui::GetIO().Framerate);
    #endif

    render->DrawContextMenu();
    render->Console();

    if (isFont)
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".cpp,.h,.hpp", ".");
        
    /* End of window */
    ImGui::End();
}
