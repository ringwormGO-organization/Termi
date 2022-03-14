/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Neofetch main file
*/

#pragma once

#include <iostream>
#include <vector>
#include <fstream>

static inline void native_cpuid(unsigned int *eax, unsigned int *ebx, unsigned int *ecx, unsigned int *edx)
{
    /* ecx is often an input as well as an output. */
    asm volatile
    ("cpuid"
        : "=a" (*eax),
            "=b" (*ebx),
            "=c" (*ecx),
            "=d" (*edx)
        : "0" (*eax), "2" (*ecx)
    );
}

bool isWanted(const std::string & line, std::string field) 
{
    return (line.find(field) != std::string::npos);
}

std::vector<std::string> explode(const std::string& str, const char& ch) 
{
    std::string next;
    std::vector<std::string> result;

    // For each character in the string.
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) 
    {
        // If we've hit the terminal character.
        if (*it == ch) {
            // If we have some characters accumulated.
            if (!next.empty()) {
                // Add them to the result vector.
                result.push_back(next);
                next.clear();
            }
        } else {
            next += *it; // Accumulate the next character into the sequence.
        }
    }
    if (!next.empty())
         result.push_back(next);
    return result;
}

std::string parse(std::string field, std::string file) 
{
    std::ifstream thefile(file); // Open the file for reading.
    std::string output,line,line_pre_array;
    while (getline(thefile, line)) 
    {
        if (isWanted(line, field))
            line_pre_array = line;
    }
    thefile.close(); // Close the file.
    return line_pre_array;
}
