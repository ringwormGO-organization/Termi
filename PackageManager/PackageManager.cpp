/**
 * @author: Andrej Bartulin
 * PROJECT: Termi PackageManager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: C++ file for package manager
 * 
*/

#include "PackageManager.hpp"
#include "Database.hpp"

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

int search(std::string whatToSearch)
{
    auto search = database.find(whatToSearch);

    if (search != database.end())
    {
        std::cout << "Found " << search->first << " as " << search->second << '\n';
        return 0;
    }
    else
    {
        std::cout << "Unable to found " << whatToSearch << "!\n";
        return 1;
    }
}

void add(std::string name, std::string link)
{
    int result = search(name);

    if (result == 1)
    {
        database.insert
        (
            std::pair<std::string, std::string> (name, link)
        );

        search(name);
    }
    else
    {
        std::cout << "Already in database!\n";
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
}

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        help();
        return 0;
    }

    Init();

    if (strcmp(argv[1], "search"))
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
            if (argv[3] == NULL)
            {
                printf("There is no download link or command!");
            }
            else
            {
                add(argv[2], argv[3]);
            }
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
