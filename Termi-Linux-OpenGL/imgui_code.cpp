/**
 * @author Andrej Bartulin
 * @mainteiner Stjepan Bilić Matišić
 * PROJECT: Termi-linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui_code.hpp"

void print()
{
    std::cout << "Test string\n";
}

void main_code()
{
    using namespace std;

    // ImGUI window creation
    ImGui::Begin("ImGUI window");

    if (ImGui::Button("Print"))
        print();

    ImGui::End();
}
