/*
 * PROJECT: Termi PackageManager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Even if we use C++, this program will be very easy to convert to C (that is why we use .h header files)
 * 
*/

#pragma once

#include <iostream> /* we use it only for std::string, for C programs use char name[MAX_LENGTH_NAME]; */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_NAME 250 /* maximum length of program */
#define MAX_LENGTH_LINK 500 /* maximum length of link */
#define MAX_DATABASE 250 /* maximum elements in database */

/* line from text file */
char line[MAX_LENGTH_LINK];

/* struct which contains operarting system name */
struct host_info
{
    std::string name;
};

/* struct which contains informations about program */
struct program
{
    std::string name;
    std::string link;
};

/* struct which contains link which read links form text file */
struct link_database
{
    std::string link;
};

/* struct which contains settings for package manager */
struct Settings
{
    int install_mode;
    std::string default_path;
};

/* Functions */
void InitDatabase(char* link);
void help();
void search(char* link);

/* Functions which initialize database and set up other things too */
void Init();
