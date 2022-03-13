/**
 * @author: Andrej Bartulin
 * PROJECT: Termi Package Manager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main header file for package manager
 * 
*/

#pragma once

#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_NAME 250 /* maximum length of program */
#define MAX_LENGTH_LINK 500 /* maximum length of link */
#define MAX_DATABASE 250 /* maximum elements in database */

/* GitHub repo link */
const char* repo_link = "https://github.com/ringwormGO-organization/Termi";

/* struct which contains settings for package manager */
struct Settings
{
    int install_mode;
    std::string default_path;
};

/* struct which contains information about Termi installation */
struct Install
{
    std::string host;
    std::string install_path;
    bool isAdditionEnabled;
};

/* Required for curl */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/* Class which contains functions  */
class Functions
{
    public:
        /* Set up what we need */
        Functions();

        /* Help function */
        void Help(int type);

        /* Serach function - returns a command or link */
        const char* Search(std::string name);

        /* Add function */
        void Add(std::string name, std::string link);

        /* Remove function */
        void Remove(std::string name);

        /* Install functions */
        int Install(std::string name);
        int Install(std::string name, std::string link);

        /* Uninstall functions */
        void Uninstall(std::string name);
        void Uninstall(std::string name, std::string path);

        /* Settings function */
        void Settings();

    private:
        /* Download a file or folder */
        int Download(const char* name, int type);
};

extern Settings settings;
extern Install install;

extern Functions* functions;
