/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file for implementing commands code
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL
*/

#include "imgui_code.hpp"

using namespace std;

int base64(std::vector<std::string>& vect)
{
    vector<string> out;

    if (vect[1] == "-e")
    {
        for (auto x : vect)
        {
            out.push_back(base64_encode(x));
        }

        vector<decltype(out)::value_type>(out.begin()+2, out.end()).swap(out);
        
        console.AddLog("Result:\n");
        
        for (auto y : out)
        {
            console.AddLog("%s", y.c_str());
        }

        return 0;
    }

    else if (vect[1] == "-d")
    {
        for (auto x : vect)
        {
            out.push_back(base64_decode(x));
        }

        vector<decltype(out)::value_type>(out.begin()+2, out.end()).swap(out);
        
        console.AddLog("Result:\n");
        
        for (auto y : out)
        {
            console.AddLog("%s", y.c_str());
        }

        return 0;
    }

    else
    {
        console.AddLog("Unknown parametar '%s'! Returning 1...\n", vect[1].c_str());
        return 1;
    }
}

int cd(std::vector<std::string>& vect)
{
    return chdir(vect[1].c_str());
}

int change_setting(std::vector<std::string>& vect)
{
    try
    {
        if (vect.size() != 3)
        {
            console.AddLog("No setting specified!");
            return 1;
        }

        int setting = stoi(vect[1]);

        if (setting != 5 && setting != 8)
        {
            return static_cast<int>(console.Settings(setting, stof(vect[2])));
        }

        else if (setting == 5)
        {
            console.startup_command = vect[2];
            console.Settings(5, 0);
        }

        else if (setting == 8)
        {
            console.font_name = vect[2];
            console.Settings(8, 0);
        }
    }

    catch(const std::exception& e)
    {
        console.AddLog("Catched exception. Exception result: '%s'", e.what());
        return 2;
    }
}

int echo(std::vector<std::string>& vect)
{
    if (isStarting(vect[1], "$"))
    {
        console.AddLog("Variables not supported yet!\n");
        return 2;
    }

    else
    {
        for (string x : vect)
        {
            console.AddLog("%s", x.c_str());
        }
    }

    return 0;
}

int find_command(std::vector<std::string>& vect)
{
    vector<string> out;

    out.push_back("list");
    out.push_back(vect[1]);
    out.push_back("!");

    list_dir(out);

    if (find(filesys.begin(), filesys.end(), vect[2]) != filesys.end())
    {
        console.AddLog("File/Directory '%s' found!\n", vect[2].c_str());
    }
    
    else
    {
        console.AddLog("File/Directory '%s' not found!\n", vect[2].c_str());

        out.clear();
        filesys.clear();

        return 1;
    }

    out.clear();
    filesys.clear();

    return 0;
}

int list_dir(std::vector<std::string>& vect)
{
    if (vect[1] != "")
    {
        chdir(vect[1].c_str());
    }

    DIR *dr;
    struct dirent *en;
    dr = opendir("."); /* open all directory */

    if (dr) 
    {
        while ((en = readdir(dr)) != NULL) 
        {
            filesys.push_back(en->d_name);
        }

        closedir(dr); /* close all directory */
        sort(filesys.begin(), filesys.end());

        for (auto x : filesys)
        {
            console.AddLog("%s\n", x.c_str());
        }

        console.AddLog("Total: %d\n", filesys.size());

        if (vect[2] == "")
        {
            filesys.clear();
        }
    }

    else
    {
        return 2;
    }

    return 0;
}

int new_dir(std::vector<std::string>& vect)
{
    if (mkdir(vect[1].c_str(), 0777) == -1)
    {
        console.AddLog("Error while creating directory!\n");
        return 2;
    }

    else
    {
        console.AddLog("Directory %s created!\n", vect[1].c_str());
        return 0;
    }
}

int neofetch(std::vector<std::string>& vect)
{
    /* Username and computer name */
    gethostname(info.computer, HOST_NAME_MAX);
    getlogin_r(info.user, LOGIN_NAME_MAX);

    /* OS */
    #ifdef _WIN32
        info.OS = "Windows32";
    #elif _WIN64
        info.OS = "Windows64";
    #elif __APPLE__ || __MACH__
        info.OS = "Mac OSX";
    #elif __linux__
        info.OS = "(GNU/)Linux";
    #elif __FreeBSD__
        info.OS = "FreeBSD";
    #elif __unix || __unix__
        info.OS = "Unix";
    #else
        info.OS = "Other";
    #endif

    /* CPU */
    string cpu;
    string line_pre_array = parse("model name", "/proc/cpuinfo");
    vector<string> result = explode(line_pre_array, ':');
    cpu = result[1];
    cpu = regex_replace(cpu, regex("^ +"), "");
    info.cpu = cpu;

    /* Memory */
    string total_line = parse("MemTotal", "/proc/meminfo");
    vector<string> total_line_vector = explode(total_line, ' ');
    int total_size = stoi(total_line_vector[1]);
    if (total_size > 1024) 
    {
        int total = total_size / 1024;
        string message_total = to_string(total);
        string message = message_total + "MB";
        info.memory = message;
    }

    else 
    {
        string message_total = to_string(total_size);
        string message = message_total + "KB";
        info.memory = message;
    }

    /* Uptime */
    chrono::milliseconds uptime(0u);
    double uptime_seconds;
    if (ifstream("/proc/uptime", ios::in) >> uptime_seconds)
    {
        uptime = chrono::milliseconds
        (
            static_cast<unsigned long long>(uptime_seconds * 1000.0)
        );
    }

    else
    {
        return 2;
    }

    info.uptime = uptime_seconds / 3600;

    console.AddLog("\n");
    console.AddLog("\t %s @ %s\n", info.user, info.computer);
    console.AddLog("--------------------------------------------\n");

    console.AddLog("\n");
    console.AddLog("\tOperating system: %s, %s\t\n", info.OS.c_str(), distro().c_str());
    console.AddLog("\tUptime: %d hours\t\n\n", info.uptime);
    console.AddLog("\tPackages: %s\t\n", packages().c_str());

    console.AddLog("\tCPU: %s\t\n", info.cpu.c_str());
    console.AddLog("\tMemory: %s\t\n", info.memory.c_str());
    console.AddLog("\n");

    return 0;
}

int openfile(std::vector<std::string>& vect)
{
    fstream my_file;
    string file = vect[1];

    my_file.open(file, ios::in);
    if (!my_file) 
    {
        console.AddLog("No such file %s!\n", file.c_str());
        return 1;
    }

    else 
    {
        string str; 
        while (getline(my_file, str))
        {
            console.AddLog("%s\n", str.c_str());
        }
    }
    console.AddLog("\n");
    my_file.close();

    return 0;
}

int ttime(std::vector<std::string>& vect)
{
    auto givemetime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    console.AddLog("%s", ctime(&givemetime));
    return 0;
}

int rm(std::vector<std::string>& vect)
{
    return remove(vect[1].c_str());
}

int whoami(std::vector<std::string>& vect)
{
    char user[HOST_NAME_MAX];

    getlogin_r(user, HOST_NAME_MAX);

    console.AddLog("%s\n", user);
}

int writefile(std::vector<std::string>& vect)
{
    auto mode = ios::in;

    string file = vect[1];

    if (!console.CheckFile(file.c_str()))
    {
        fstream new_file(file, mode);
    }

    fstream myfile(file, mode);
    myfile << vect[2];
    myfile.close();

    return 0;
}

int yes(std::vector<std::string>& vect)
{
    /*while (true)
    {
        console.AddLog("yes\n");
    }*/

    for (int i = 0; i < 100000; i++)
    {
        console.AddLog("y\n");
    }

    return 0;
}

int calc(std::vector<std::string>& vect)
{
    string op = vect[1];
    float num1 = stof(vect[2]);
    float num2 = stof(vect[3]);

    try
    {
        if (!strcmp(op.c_str(), "+"))
        {
            console.AddLog("Result: %f\n", num1 + num2);
            return 0;
        }

        else if(!strcmp(op.c_str(), "-"))
        {
            console.AddLog("Result: %f\n", num1 - num2);
            return 0;
        }

        else if (!strcmp(op.c_str(), "*"))
        {
            console.AddLog("Result: %f\n", num1 * num2);
            return 0;
        }

        if (!strcmp(op.c_str(), "/"))
        {
            if (num2 == 0)
            {
                console.AddLog("Cannot divide with 0!\n");
                return 1;
            }

            else
            {
                console.AddLog("Result: %f\n", num1 / num2);
                return 0;
            }
        }

        else
        {
            console.AddLog("Invalid operator %s!\n", op.c_str());
            return 1;
        }

        return 0;
    }

    catch(const std::exception& e)
    {
        console.AddLog("Catched exception. Exception result: %s", e.what());
        return 2;
    }
}

/* Credits to StjepanBM1 */ 
int geocalc(std::vector<std::string>& vect)
{
    string EXT = "EXT";
    string SUR = "SUR";
    string TRA = "TRA";
    string REC = "REC";
    string SQU = "SQU";

    string ext_or_sur = vect[1];

    try
    {
        if (ext_or_sur == SUR)
        {
            string TRA = "TRA";
            string REC = "REC";
            string SQU = "SQU";

            string rec_or_squ = vect[2];

            if (rec_or_squ == REC)
            {
                double x = stod(vect[3]);
                double y = stod(vect[4]);

                console.AddLog("Result: %f\n", povrsDvijustr(x, y));
            }

            else if (rec_or_squ == SQU)
            {
                double x = stod(vect[3]);

                console.AddLog("Result: %f\n", povrsKvdjustr(x));
            }

            else if (rec_or_squ == TRA)
            {
                double x = stod(vect[3]);
                double Vx = stod(vect[4]);

                console.AddLog("Result: %f\n", povrsTrokuta(x, Vx));
            }

            else
            {
                console.AddLog("Unknown input '%s'\n", rec_or_squ.c_str());
                return 1;
            }
        }

        else if (ext_or_sur == EXT)
        {
            string TRA = "TRA";
            string REC = "REC";
            string SQU = "SQU";

            string tra_or_rec_or_squ = vect[1];

            if (tra_or_rec_or_squ == TRA)
            {
                double x = stod(vect[3]);
                double y = stod(vect[4]);
                double z = stod(vect[5]);

                console.AddLog("Result: %f\n", opsgTrijustr(x, y, z));
            }

            else if (tra_or_rec_or_squ == REC)
            {
                double x = stod(vect[3]);
                double y = stod(vect[4]);

                console.AddLog("Result: %f\n", opsgDvijustr(x, y));
            }

            else if (tra_or_rec_or_squ == SQU)
            {
                int sqe = 4;

                double x = stod(vect[3]);

                console.AddLog("Result: %f\n", opsgKvdjustr(x, sqe));
            }

            else
            {
                console.AddLog("Unknown input '%s'\n", tra_or_rec_or_squ.c_str());
                return 1;
            }
        }

        else
        {
            console.AddLog("Unknown input '%s'\n", ext_or_sur.c_str());
            return 1;
        }

        return 0;
    }

    catch(const std::exception& e)
    {
        console.AddLog("Catched exception! Result: '%s'\n", e.what());
        return 2;
    }
}