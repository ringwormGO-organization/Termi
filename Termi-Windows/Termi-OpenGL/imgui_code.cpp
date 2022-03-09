/**
 * @author Andrej Bartulin
 * @mainteiner Stjepan Bilić Matišić
 * PROJECT: Termi-linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui_code.hpp"

using namespace std;

void Print()
{
    cout << "Test string\n";
}

void main_code()
{
    // ImGUI window creation
    ImGui::Begin("Termi");

    if (ImGui::Button("Print"))
        Print();

    /* End of window */
    ImGui::End();
}
