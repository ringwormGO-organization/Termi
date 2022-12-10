/**
 * @author Andrej Bartulin
 * PROJECT: Termi version
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: sysfetch header file
*/

#pragma once

#ifdef __linux__
    #include <iostream>
    #include <string>
    #include <regex>
    #include <vector>
    #include <fstream>
    #include <chrono>
    #include <algorithm>
    #include <filesystem>

    #include <stdio.h>
    #include <stdlib.h>
    #include <errno.h>
    #include <ctype.h>
    #include <unistd.h>
    #include <limits.h>
    #include <sys/unistd.h>

    enum PackageManager 
    {
        UNKNOWN,
        APK,    // apk -- package manager for Alpine Linux.
        DNF,    // dnf -- package manager for Red Hat distros.
        DPKG,   // dpkg -- same as apt.
        EOPKG,  // eopkg -- Solus package manager.
        PACMAN, // pacman -- Arch package manager.
        PIP,    // pip -- Python's package manager.
        QLIST,  // qlist -- list package info for Portage.
        RPM,    // rpm -- like dnf.
        XBPS,   // xbps -- Void Linux's package manager.
    };

    static bool isWanted(const std::string & line, std::string field) 
    {
        return (line.find(field) != std::string::npos);
    }

    static std::vector<std::string> explode(const std::string& str, const char& ch) 
    {
        std::string next;
        std::vector<std::string> result;

        // For each character in the std::string.
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

    static std::string parse(std::string field, std::string file) 
    {
        std::ifstream thefile(file); // Open the file for reading.
        std::string output,line,line_pre_array;
        while (std::getline(thefile, line)) 
        {
            if (isWanted(line, field))
                line_pre_array = line;
        }
        thefile.close(); // Close the file.
        return line_pre_array;
    }

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

    /* ------------------------------------- */

    static struct Inforamtion
    {
        char computer[256];
        char user[64];

        std::string OS = "n/a";
        int uptime = 0;

        std::string cpu = "n/a";
        std::string memory = "n/a";
    } info;

    static std::string extract(std::string file) 
    {
        std::string distro;
        std::string line_pre_array = parse("PRETTY_NAME", file);
        std::vector<std::string> result = explode(line_pre_array, '=');
        distro = result[1]; // Second element.
        // Trim `"` from the std::string.
        distro.erase(remove(distro.begin(), distro.end(), '\"'), distro.end());
        return distro;
    }

    /* 
    * Parse `/etc/os-release` for the PRETTY_NAME std::string
    * and extract the value of the variable.
    * Returns the name of the distro.
    * Example: Gentoo/Linux.
    * 
    * In own function
    */
    static std::string distro() 
    {
        // Check if running Android.
        if (std::system("which getprop > /dev/null 2>&1")) 
        {
            // No getprop command, resume as normal.
            std::filesystem::path bedrock_file = "/bedrock/etc/os-release";
            std::filesystem::path normal_file = "/etc/os-release";
            std::filesystem::path weird_file = "/var/lib/os-release";
            if (std::filesystem::exists(bedrock_file)) 
            {
                return extract("/bedrock/etc/os-release");
            } else if (std::filesystem::exists(normal_file)) 
            {
                return extract("/etc/os-release");
            } else if (std::filesystem::exists(weird_file)) 
            {
                return extract("/var/lib/os-release");
            } 
            else 
            {
                return "N/A (could not read '/bedrock/etc/os-release', '/etc/os-release', nor '/var/lib/os-release')";
            }
        } 
        else 
        {
            // getprop command found, return Android version.
            const std::string& command = "getprop ro.build.version.release";
            std::system((command + " > temp.txt").c_str());
    
            std::ifstream ifs("temp.txt");
            std::string ret{std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
            ifs.close(); // must close the inout stream so the file can be cleaned up
            if (remove("temp.txt") != 0) 
            {
                perror("Error deleting temporary file");
            }
            std::string message = "Android " + ret;
            message.erase(remove(message.begin(), message.end(), '\n'), message.end());
            return message;
        }
    };

    /* 
    * Run the command and count the lines of output, 
    * optionally subtract from the count to account for extra lines,
    * then assemble and return the message as a std::string.
    * 
    * In own function
    */
    static std::string count(std::string cmd, std::string manager, int remove = 0) 
    {
        const std::string& command = cmd + "| wc -l";
        std::system((command + " > temp.txt").c_str());
    
        std::ifstream ifs("temp.txt");
        std::string ret{std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
        ifs.close(); // must close the inout stream so the file can be cleaned up
        if (std::remove("temp.txt") != 0) 
        {
            perror("Error deleting temporary file");
        }
        int amount = std::stoi(ret);
        amount = amount - remove;
        std::string message = ret + " (" + manager + ")";
        message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());
        return message;
    };

    static PackageManager findPackageManager() 
    {
        if (system("which apk > /dev/null 2>&1") == 0) 
        {
            return APK;
        } 

        else if (system("which dnf > /dev/null 2>&1") == 0) 
        {
            return DNF;
        } 

        else if (system("which dpkg-query > /dev/null 2>&1") == 0) 
        {
            return DPKG;
        } 

        else if (system("which eopkg > /dev/null 2>&1") == 0) 
        {
            return EOPKG;
        } 

        else if (system("which pacman > /dev/null 2>&1") == 0) 
        {
            return PACMAN;
        }

        else if (system("which qlist > /dev/null 2>&1") == 0) 
        {
            return QLIST;
        } 

        else if (system("which rpm > /dev/null 2>&1") == 0) 
        {
            return RPM;
        } 

        else if (system("which xbps-query > /dev/null 2>&1") == 0) 
        {
            return XBPS;
        } 

        else 
        {
            return UNKNOWN;
        }
    };

    /* Return package counts */
    static std::string packages() 
    {
        switch (findPackageManager()) 
        {
            case APK:
                return count("apk info", "apk");
            case DNF:
                return count("dnf list installed", "dnf");
            case DPKG:
                return count("dpkg-query -f '${binary:Package}\n' -W", "dpkg");
            case EOPKG:
                return count("eopkg list-installed", "eopkg");
            case PACMAN:
                return count("pacman -Qq", "pacman");
            case QLIST:
                return count("qlist -I", "Portage");
            case RPM:
                return count("rpm -qa", "rpm");
            case XBPS:
                return count("xbps-query -l", "xbps");
            default: return "N/A (no supported pacakge managers found)";
        }
    };
#endif
