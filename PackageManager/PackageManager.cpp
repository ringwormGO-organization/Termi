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
    }
}

void help()
{
    printf("There is no enough arguments! See help down below\n\n");
    printf("search <software name> - search software in database\n");
    printf("add <software name> - add software download link to database\n");
    printf("remove <software name> - remove software from database\n");
    printf("install <software name> - install software, if it is not in database, you can add it or type download link\n");
    printf("uninstall <software name> - uninstall software from computer\n");
    printf("settings - open settings\n\n");
    printf("Sometimes, instead of donwload link, you can use command which you normally paste to terminal\n");
    printf("Also is recommended to run this package manager as sudo");
    printf("\n");
}

void search(char* link)
{
    FILE* f = fopen("database.txt", "r");

    while (fgets(line, MAX_LENGTH_LINK, f))
    {
        if (!strcmp(line, link)) /* I don't know why is not here but work */
        {
            printf("Found link %s.\n", line);
        }
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
        host.name = "GNU/Linux";
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
    char input[MAX_LENGTH_NAME];

    if (argc == 1)
    {
        help();
        return 0;
    }

    Init();

    if (strcmp(argv[1], "serach"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!");
        }
        else
        {
            search(argv[2]);
        }
    }

    else if (strcmp(argv[1], "add"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!");
        }
        else
        {
            /* add(argv[2]); */
        }
    }

    else if (strcmp(argv[1], "remove"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!");
        }
        else
        {
            /* remove(argv[2]); */
        }
    }

    else if (strcmp(argv[1], "install"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!");
        }
        else
        {
            /* install(argv[2]); */
        }
    }

    else if (strcmp(argv[1], "uninstall"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!");
        }
        else
        {
            /* uninstall(argv[2]); */
        }
    }

    else if (strcmp(argv[1], "uninstall"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!");
        }
        else
        {
            /* uninstall(argv[2]); */
        }
    }

    else if (strcmp(argv[1], "settings"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no setting to change!");
        }
        else
        {
            /* settings(argv[2]); */
        }
    }

    else if (strcmp(argv[1], "help"))
    {
        help();
    }

    else
    {
        help();
    }

    return 0;
}
