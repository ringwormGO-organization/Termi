/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Translation file
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL
*/

#pragma once

#include <vector>
#include <string>

namespace Translation
{
    static std::vector<std::string> English = {"Input", "Terminal", "Edit", "About", "New Tab", "New profile", "Exit", "Font picker", "Change theme", "Change language", "About Termi", "About Dear ImGui"};
    static std::vector<std::string> Croatian = {"Unos", "Ljuska", "Uredi", "O Termiju", "Nova kartica", "Novi profil", "Izađi", "Odaberi font", "Promijeni temu", "Promijeni jezik", "O Termiju", "O Dear ImGui-u"};

    /**
     * Naming convention for IDs fot strings
     * 0: Input
     * 1: Terminal
     * 2: Edit
     * 3: About
     * 4: New Tab
     * 5: New profile
     * 6: Exit
     * 7: Font picker
     * 8: Change theme
     * 9: Change language
     * 10: About Termi
     * 11: About Dear ImGui
    */
};
