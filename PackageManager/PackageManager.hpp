/**
 * @author: Andrej Bartulin
 * PROJECT: Termi PackageManager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Header file for package manager
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

/* struct which contains settings for package manager */
struct Settings
{
    int install_mode;
    std::string default_path;
};

/* Functions */
void help();
int search(std::string whatToSearch);
void add(std::string name, std::string link);

/* Functions which initialize database and set up other things too */
void Init();
