/*
 * PROJECT: Termi PackageManager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Even if we use C++, this program will be very easy to convert to C (that is why we use .h header files)
 * 
*/

#include "PackageManager.h"

void InitDatabase(char* link)
{
    int i, j;

    link_database database[MAX_DATABASE];

    for (i = j = 0; i < MAX_DATABASE; i++)
    {
        database[i].link = link;
        std::cout << database[i].link << std::endl;
    }
}

void Init()
{
    host_info host;

    #ifdef _WIN32
        host.name = "Windows32";
    #elif _WIN64
        host.name = "Windows64";
    #elif __APPLE__ || __MACH__
        host.name = "Mac OSX";
    #elif __linux__
        host.name = "Linux";
    #elif __FreeBSD__
        host.name = "FreeBSD";
    #elif __unix || __unix__
        host.name = "Unix";
    #else
        host.name = "Other";
    #endif

    FILE* f = fopen("database.txt", "r");
    unsigned int lines;

    if (f == NULL)
    {
        printf("There is no file to read database!");
        return;
    }

    while (fgets(line, MAX_LENGTH_LINK, f))
    {
        InitDatabase(line);
        lines++;
    }
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("There is no enough arguments! See help down below\n\n");
        printf("search <software name> - search software in database\n");
        printf("add <software name> - add software download link to database\n");
        printf("remove <software name> - remove software from database\n");
        printf("install <software name> - install software, if it is not in database, you can add it or type download link\n");
        printf("uninstall <software name> - uninstall software from computer\n");
        printf("settings - open settings\n");
        printf("\n");
        return 0;
    }

    Init();

    return 0;
}
