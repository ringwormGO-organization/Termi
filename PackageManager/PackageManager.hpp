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
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "indicators.hpp"

/* For Unix systems package manager will include limits.h */
#ifdef USE_UNIX_LIMITS
        #define NGROUPS_MAX    65536	/* supplemental group IDs are available */
        #define ARG_MAX       131072	/* # bytes of args + environ for exec() */
        #define LINK_MAX         127	/* # links a file may have */
        #define MAX_CANON        255	/* size of the canonical input queue */
        #define MAX_INPUT        255	/* size of the type-ahead buffer */
        #define NAME_MAX         255	/* # chars in a file name */
        #define PATH_MAX        4096	/* # chars in a path name including nul */
        #define PIPE_BUF        4096	/* # bytes in atomic write to a pipe */
        #define XATTR_NAME_MAX   255	/* # chars in an extended attribute name */
        #define XATTR_SIZE_MAX 65536	/* size of an extended attribute value (64k) */
        #define XATTR_LIST_MAX 65536	/* size of extended attribute namelist (64k) */
#else
    #include <limits.h>
#endif

/* GitHub repo link */
const char* repo_link = "https://github.com/ringwormGO-organization/Termi";

/* Operating system information */
int host;

/* struct which contains settings for package manager */
struct Settings
{
    int install_mode;
    std::string default_path;
};

/* Struct which contains information about Termi installation */
struct Install
{
    std::string install_path;
    bool isAdditionEnabled;
};

/* Required for curl */
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) 
{
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

/* Required for us */
int isEnding (std::string const &fullString, std::string const &ending) 
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } 

    else 
    {
        return 1;
    }
}

/* Class which contains functions  */
class Functions
{
    public:
        /* Set up what we need */
        Functions();

        /* Help function */
        void Help(int type, char* argument);

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
        /* Download a file or folder - found link from database */
        int Download(const char* name);
        /* Download a file or folder*/
        int Download(const char* name, const char* link);

        static int Progress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
};

extern Settings settings;
extern Install install;

extern Functions* functions;
