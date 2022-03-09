/**
 * @author: Andrej Bartulin
 * PROJECT: Termi PackageManager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: C++ file for package manager
 * 
*/

#include "PackageManager.hpp"
#include "Database.hpp"

void help(int type)
{
    /**
     * 0: Do not print any argument warning and/or error
     * 1: Print no argument error.
     * 2. Print wrong argument error.
    */

    printf("Termi package manager designed to install addition to Termi\n\n");

    switch (type)
    {
        case 0:
            break;

        case 1:
            printf("There is no enough arguments! See help down below\n\n");
            break;

        case 2:
            printf("There is wrong argument/arguments! See help down below\n\n");
            break;

        default:
            break;
    }
    
    printf("search <software name> - search software in database\n");
    printf("add <software name> - add software download link to database\n");
    printf("rm <software name> - remove software from database\n");
    printf("install <software name> - install software, if it is not in database, you can add it or type download link\n");
    printf("uninstall <software name> - uninstall software from computer\n");
    printf("settings - open settings\n\n");
    printf("Sometimes, instead of donwload link, you can use command which you normally paste to terminal\n");
    printf("Also is recommended to run this package manager as administartor/sudo");
    printf("\n");
}

void search(std::string whatToSearch)
{
    auto search = database.find(whatToSearch);

    if (search != database.end())
    {
        std::cout << "Found " << search->first << " as " << search->second << '\n';
    }
    else
    {
        std::cout << "Unable to found " << whatToSearch << "!\n";
    }
}

void add(std::string name, std::string link)
{
    auto position(end(database));
    position = database.insert
    (
        position, 
        { 
            name, 
            link 
        }
    );

    search(name);
}

void Init()
{
    host_info host;

    #ifdef _WIN32
        host.name = "Windows32";
        system("cls");
    #elif _WIN64
        host.name = "Windows64";
        system("cls");
    #elif __APPLE__ || __MACH__
        host.name = "Mac OSX";
    #elif __linux__
        host.name = "GNU/Linux";
        system("clear");
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
        help(1);
        return 0;
    }

    Init();

    if (strlen(argv[1]) == 6)
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            search(argv[2]);
        }
    }

    if (strlen(argv[1]) == 3)
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            if (argv[3] == NULL)
            {
                printf("There is no download link or command!\n");
            }
            else
            {
                add(argv[2], argv[3]);
            }
        }
    }

    else if (strlen(argv[1]) == 2)
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            /* remove(argv[2]); */
        }
    }

    else if (strlen(argv[1]) == 2)
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            /* install(argv[2]); */
        }
    }

    else if (strlen(argv[1]) == 9)
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            /* uninstall(argv[2]); */
        }
    }

    else if (strlen(argv[1]) == 8)
    {
        if (argv[2] == NULL)
        {
            printf("There is no setting to change!\n");
        }
        else
        {
            /* settings(argv[2]); */
        }
    }

    else if (strlen(argv[1]) == 4)
    {
        help(0);
    }

    else
    {
        help(2);
    }

    return 0;
}
