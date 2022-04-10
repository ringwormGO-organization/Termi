/**
 * @author: Andrej Bartulin
 * PROJECT: Termi Package Manager
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main C++ file for package manager
 * 
*/

#ifdef _WIN32
        #define USE_UNIX_LIMITS
    #elif _WIN64
        #define USE_UNIX_LIMITS
    #else
#endif
#include "PackageManager.hpp"
#include "Database.hpp"

#include <curl/curl.h>
#include <curl/easy.h>

Settings settings;
Install install;

Functions* functions;

/* Required for curl */
// https://curl.se/libcurl/c/CURLOPT_XFERINFOFUNCTION.html
int download_progress_callback(void* clientp, curl_off_t dltotal,
                               curl_off_t dlnow, curl_off_t ultotal,
                               curl_off_t ulnow)
{
    indicators::ProgressBar* progress_bar =
        static_cast<indicators::ProgressBar*>(clientp);

    if (progress_bar->is_completed())
    {
        ;
    }
    else if (dltotal == 0)
    {
        progress_bar->set_progress(0);
    }
    else
    {
        int percentage =
            static_cast<float>(dlnow) / static_cast<float>(dltotal) * 100;
        progress_bar->set_progress(percentage);
    }

    // If your callback function returns CURL_PROGRESSFUNC_CONTINUE it will
    // cause libcurl to continue executing the default progress function. return
    // CURL_PROGRESSFUNC_CONTINUE;

    return 0;
}

int download_progress_default_callback(void* clientp, curl_off_t dltotal,
                                       curl_off_t dlnow, curl_off_t ultotal,
                                       curl_off_t ulnow)
{
    return CURL_PROGRESSFUNC_CONTINUE;
}

Functions::Functions()
{

}

/* Help function */
void Functions::Help(int type, char* argument)
{
    /**
     * 0: Do not print any argument warning and/or error
     * 1: Print no argument error.
     * 2. Print wrong argument error.
    */

    printf("Termi package manager designed to install addition to Termi\n");
    printf("Termi's GitHub repo: %s\n\n", repo_link);

    switch (type)
    {
        case 0:
            break;

        case 1:
            printf("There is no enough arguments! See help down below\n\n");
            break;

        case 2:
            printf("'%s' is wrong argument! See help down below\n\n", argument);
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
    printf("Sometimes, instead of download link, you can use command which you normally paste to terminal\n");
    printf("Also is recommended to run this package manager as administartor/sudo");
    printf("\n");
}

/* Serach function - returns a command or link */
const char* Functions::Search(std::string name)
{
    auto search = database.find(name);

    if (search != database.end())
    {
        std::cout << "Found " << search->first << " as " << search->second << '\n';
    }
    else
    {
        std::cout << "Unable to found " << name << "!\n";
    }

    return search->second.c_str();
}

/* Add function */
void Functions::Add(std::string name, std::string link)
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

    Search(name);
}

/* Remove function */
void Functions::Remove(std::string name)
{
    database.erase(name);

    Search(name);
}

/* Install functions */
int Functions::Install(std::string name)
{
    if (Download(name.c_str()) == 0)
    {
         if (isEnding(name, ".tar.gz") | isEnding(name, ".zip"))
        {
            /* unpack */
        }

        else
        {
            /* move to right folder */
        }

        return 0;
    }
    else
    {
        printf("Package Manager can't find name or link. Try add name or link to database or try call this function with following arguments: \n");
        printf(" <name> <link> \n");
        printf("If you still can't download, report an issue on Termi's GitHub (see help for link).\n");
        return 1;
    }
}

int Functions::Install(std::string name, std::string link)
{
    if (Download(name.c_str(), link.c_str()) == 0)
    {
        if (isEnding(name, ".tar.gz") | isEnding(name, ".zip"))
        {
            /* unpack */
        }

        else
        {
            /* move to right folder */
        }

        return 0;
    }
    
    else
    {
        return 1;
    }
}

/* Uninstall functions */
void Functions::Uninstall(std::string name)
{

}

void Functions::Uninstall(std::string name, std::string path)
{

}

/* Settings function */
void Functions::Settings()
{
    int id;

    std::string temp_path;

    printf("Enter id of setting to change (zero is help): ");
    scanf("%d", &id);

    switch (id)
    {
        default:
            printf("Wrong setting id!");
            break;
    }
}

/* PRIVATE STUFF OF CLASS */

/* Download a file or folder */
int Functions::Download(const char* name)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char* url = Search(name);
    const char* outfilename = name;

    char tmpfilename[PATH_MAX];
    snprintf(tmpfilename, PATH_MAX - 1, "./%s.XXXXXX", outfilename);

    indicators::ProgressBar progress_bar
    {
        indicators::option::BarWidth{30}, indicators::option::Start{" ["},
        indicators::option::Fill{"█"}, indicators::option::Lead{"█"},
        indicators::option::Remainder{"-"}, indicators::option::End{"]"},
        indicators::option::PrefixText{outfilename},
        // indicators::option::ForegroundColor{indicators::Color::yellow},
        indicators::option::ShowElapsedTime{true},
        indicators::option::ShowRemainingTime{true},
        // indicators::option::FontStyles{
        //     std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
    };

    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(tmpfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION,
                         download_progress_callback);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA,
                         static_cast<void*>(&progress_bar));
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
        // Perform a file transfer synchronously.
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    else
    {
        return 1;
    }

    if (host == 4)
    {
        rename(tmpfilename, outfilename);
    }

    return 0;
}

int Functions::Download(const char* name, const char* link)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    const char* url = link;
    const char* outfilename = name;

    char tmpfilename[PATH_MAX];
    snprintf(tmpfilename, PATH_MAX - 1, "./%s.XXXXXX", outfilename);

    if (host == 4)
    {
        int fd = mkstemp(tmpfilename);
    }

    indicators::ProgressBar progress_bar
    {
        indicators::option::BarWidth{30}, indicators::option::Start{" ["},
        indicators::option::Fill{"█"}, indicators::option::Lead{"█"},
        indicators::option::Remainder{"-"}, indicators::option::End{"]"},
        indicators::option::PrefixText{outfilename},
        // indicators::option::ForegroundColor{indicators::Color::yellow},
        indicators::option::ShowElapsedTime{true},
        indicators::option::ShowRemainingTime{true},
        // indicators::option::FontStyles{
        //     std::vector<indicators::FontStyle>{indicators::FontStyle::bold}}
    };

    curl = curl_easy_init();                                                                                                                                                                                                                                                           
    if (curl)
    {   
        fp = fopen(tmpfilename, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION,
                         download_progress_callback);
        curl_easy_setopt(curl, CURLOPT_XFERINFODATA,
                         static_cast<void*>(&progress_bar));
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
        // Perform a file transfer synchronously.
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);

        if (res == CURLE_OK)
        {
            printf("Downloaded %s as %s.\n", tmpfilename, outfilename);
        }
        
        else
        {
            printf("Unable to download %s as %s!\n", tmpfilename, outfilename);
        }
    }

    else
    {
        return 1;
    }

    if (host == 4)
    {
        rename(tmpfilename, outfilename);
    }

    return 0;
}

/* main function */
int main(int argc, char** argv)
{
    /* OS */
    #ifdef _WIN32
        host = 1;
    #elif _WIN64
        host = 2;
    #elif __APPLE__ || __MACH__
        host = 3;
    #elif __linux__
        host = 4;
    #elif __FreeBSD__
        host = 5;
    #elif __unix || __unix__
        host = 6;
    #else
        host = 7;
    #endif

    if (argc == 1)
    {
        functions->Help(1, NULL);
        return 0;
    }

    if (!strcmp(argv[1], "search"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            functions->Search(argv[2]);
        }
    }

    else if (!strcmp(argv[1], "add"))
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
                functions->Add(argv[2], argv[3]);
            }
        }
    }

    else if (!strcmp(argv[1], "remove"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            functions->Remove(argv[2]);
        }
    }

    else if (!strcmp(argv[1], "install"))
    {
        if (argv[2] == NULL)
        {
            printf("There is no software name!\n");
        }
        else
        {
            if (argv[3] == NULL)
            {
                functions->Install(argv[2]);
            }
            else
            {
                functions->Install(argv[2], argv[3]);
            }
        }
    }

    else if (!strcmp(argv[1], "uninstall"))
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

    else if (!strcmp(argv[1], "settings"))
    {
        functions->Settings();
    }

    else if (!strcmp(argv[1], "help"))
    {
        functions->Help(0, NULL);
    }

    else
    {
        functions->Help(2, argv[1]);
    }

    return 0;
}
