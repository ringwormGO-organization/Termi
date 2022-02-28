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

char line[MAX_LENGTH_LINK];

struct host_info
{
    std::string name;
};

struct program
{
    std::string name;
    std::string link;
};

struct link_database
{
    std::string link;
};

void InitDatabase(char* link);
void search();

void Init();
