/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file for Dear ImGui
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui_code.hpp"

using namespace std;
using namespace ImGui;
using namespace Translation;

#pragma GCC diagnostic ignored "-Wformat-security"

void ok()
{
    console.AddLog("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Successfully executed!");
}

void not_ok()
{
    console.AddLog("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Not successfully executed!");
}

void ColorfulText(const string& text, const std::list<pair<char, ImVec4>>& colors = {}) 
{
    auto p = GetCursorScreenPos();
    const auto first_px = p.x, first_py = p.y;
    auto im_colors = ImGui::GetStyle().Colors;
    const auto default_color = im_colors[ImGuiCol_Text];
    string temp_str;
    struct text_t 
    {
        ImVec4 color;
        string text;
    };

    std::list<text_t> texts;
    bool color_time = false;
    ImVec4 last_color = default_color;

    for (const auto& i : text) 
    {
        if (color_time) 
        {
            const auto& f = std::find_if(colors.begin(), colors.end(), [i](const auto& v) { return v.first == i; });
            if (f != colors.end())
                last_color = f->second;
            else
                temp_str += i;
            color_time = false;
            continue;
        };
        switch (i) 
        {
            case '$':
                color_time = true;
                if (!temp_str.empty()) {
                    texts.push_back({ last_color, temp_str });
                    temp_str.clear();
                };
                break;
            default:
                temp_str += i;
        };
    };

    if (!temp_str.empty()) 
    {
        texts.push_back({ last_color, temp_str });
        temp_str.clear();
    };

    float max_x = p.x;
    for (const auto& i : texts) {
        im_colors[ImGuiCol_Text] = i.color;
        std::list<string> lines;
        temp_str.clear();
        for (const auto& lc : i.text) {
            if (lc == '\n') {
                lines.push_back(temp_str += lc);
                temp_str.clear();
            }
            else
                temp_str += lc;
        };
        bool last_is_line = false;
        if (!temp_str.empty())
            lines.push_back(temp_str);
        else
            last_is_line = true;
        float last_px = 0.f;
        for (const auto& j : lines) {
            Text(j.c_str());
            p.y += 15.f;
            last_px = p.x;
            max_x = (max_x < last_px) ? last_px : max_x;
            p.x = first_px;
        };
        const auto& last = lines.back();
        if (last.back() != '\n')
            p.x = last_px;
        else
            p.x = first_px;
        if (!last_is_line)
            p.y -= 15.f;
        if (i.text.back() != '\n')
            p.x += CalcTextSize(last.c_str()).x;
    };
    im_colors[ImGuiCol_Text] = default_color;
    Dummy({ max_x - p.x, p.y - first_py });
};

void split_str(string const &str, const char delim, vector<string> &out)  
{  
    /* create a stream from the string */  
    stringstream s(str);  
        
    string s2;  
    while (getline (s, s2, delim))  
    {  
        out.push_back(s2); /* store the string in s2 */  
    }
}

Console console;
Renderer* render;

int base64(std::vector<std::string>& vect)
{
    if (vect[1] == "-e")
    {
        string result = base64_encode(vect[2]);
        console.AddLog("String '%s' is successfully encoded to Base64.\n", vect[2].c_str());
        console.AddLog("Result is: '%s'\n", result.c_str());
        return 0;
    }

    else if (vect[1] == "-d")
    {
        string result = base64_decode(vect[2]);
        console.AddLog("String '%s' is successfully decoded.\n", vect[2].c_str());
        console.AddLog("Result is: '%s'\n", result.c_str());
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
    int setting = stoi(vect[1]);

    try
    {
        if (setting != 5 && setting != 8)
        {
            return static_cast<int>(render->Settings(setting, stof(vect[2])));
        }
        
        else if (setting == 5)
        {
            startup_command = vect[2];
            render->Settings(5, 0);
        }

        else if (setting == 8)
        {
            font_name = vect[2];
            render->Settings(8, 0);
        }
    }
    
    catch(const std::exception& e)
    {
        console.AddLog("Catched exception. Exception result: %s", e.what());
        return 1;
    }
}

int echo(std::vector<std::string>& vect)
{
    if (isStarting(vect[1], "$"))
    {
        console.AddLog("Variables not supported yet!\n");
        return 1;
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

int list_dir(std::vector<std::string>& vect)
{
    if (vect[1] == "")
    {
        DIR *dr;
        struct dirent *en;
        dr = opendir("."); //open all directory
        if (dr) 
        {
            while ((en = readdir(dr)) != NULL) 
            {
                console.AddLog("%s\n", en->d_name); //print all directory name
            }
            closedir(dr); //close all directory
            console.AddLog("\n");
        }

        else
        {
            return 1;
        }
    }

    else
    {
        chdir(vect[1].c_str());

        DIR *dr;
        struct dirent *en;
        dr = opendir("."); //open all directory
        if (dr) 
        {
            while ((en = readdir(dr)) != NULL) 
            {
                console.AddLog("%s\n", en->d_name); //print all directory name
            }
            closedir(dr); //close all directory
            console.AddLog("\n");
        }

        else
        {
            return 1;
        }
    }

    return 0;
}

int new_dir(std::vector<std::string>& vect)
{
    if (mkdir(vect[1].c_str(), 0777) == -1)
    {
        console.AddLog("Error while creating directory!\n");
        return 1;
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
        return 1;
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

    if (render->CheckFile(file.c_str()) != 0)
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
        return 1;
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
        return 1;
    }
}

/*
 * Console class - everything for drawing and managing console
 * Code for functions here
 * Code from imgui_demo.cpp
*/
Console::Console()
{
    FullClearLog();
    memset(InputBuf, 0, sizeof(InputBuf));
    HistoryPos = -1;

    // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
    Commands.push_back("help");
    Commands.push_back("credits");
    Commands.push_back("clear");
    Commands.push_back("cls");
    Commands.push_back("exit");

    for (auto& x : commands)
    {
        Commands.push_back(x.first.c_str());
    }

    sort(Commands.begin(), Commands.end());

    AutoScroll = true;
    ScrollToBottom = false;

    AddLog("Termi> ");
}

Console::~Console()
{
    FullClearLog();
    for (int i = 0; i < History.Size; i++)
        free(History[i]);
}

void Console::ClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();

    TypeTermi();
}

void Console::FullClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();
}

void Console::AddLog(const char* fmt, ...)
{
    // FIXME-OPT
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf) - 1] = 0;
    va_end(args);
    Items.push_back(Strdup(buf));
}

void Console::Draw()
{
    // TODO: display items starting from the bottom

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = GetStyle().ItemSpacing.y + GetFrameHeightWithSpacing();
    BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (BeginPopupContextWindow())
    {
        if (Selectable("Clear")) ClearLog();
        if (Selectable("Copy")) Copy = true;
        EndPopup();
    }

    /* 
        *  Display every line as a separate entry so we can change their color or add custom widgets.
        *  If you only want raw text you can use TextUnformatted(log.begin(), log.end());
        *  NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
        *  to only process visible items. The clipper will automatically measure the height of your first item and then
        *  "seek" to display only items in the visible area.
        *  To use the clipper we can replace your standard loop:
        *      for (int i = 0; i < Items.Size; i++)
        *  With:
        *      ImGuiListClipper clipper;
        *      clipper.Begin(Items.Size);
        *      while (clipper.Step())
        *          for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        *  - That your items are evenly spaced (same height)
        *  That you have cheap random access to your elements (you can access them given their index,
        *  without processing all the ones before)
        *   You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
        *  We would need random-access on the post-filtered list.
        * A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
        * or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
        * and appending newly elements as they are inserted. This is left as a task to the user until we can manage
        * to improve this example code!
        * If your items are of variable height:
        * - Split them into same height items would be simpler and facilitate random-seeking into your list.
        * - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
    */
    PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    if (Copy)
        LogToClipboard();
    for (int i = 0; i < Items.Size; i++)
    {
        const char* item = Items[i];
        ColorfulText(item, {{'w', white}, {'b', blue}, {'d', grey}, {'l', lgrey}, {'f', green}, {'m', lime}, {'y', yellow}, {'p', purple}, {'r', red}, {'o', orange}});
    }
    if (Copy)
        LogFinish();

    if (ScrollToBottom || (AutoScroll && GetScrollY() >= GetScrollMaxY()))
        SetScrollHereY(1.0f);
    ScrollToBottom = false;

    PopStyleVar();
    EndChild();
    Separator();

    bool reclaim_focus = false;
    if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0) && !help_focus)
    {
        ImGui::SetKeyboardFocusHere(0);
        help_focus = true;
    }

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (InputText(cwd, InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
    {
        s = InputBuf;
        Strtrim(s);
        if (s[0])
            ExecCommand(s);
        strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    SetItemDefaultFocus();
    if (reclaim_focus)
        SetKeyboardFocusHere(-1); // Auto focus previous widget
}

void Console::ExecCommand(string command_line, ...)
{
    /* 
        * Insert into history. First find matchand delete it so it can be pushed to the back.
        * This isn't trying to be smart or optimal
    */
    HistoryPos = -1;
    for (int i = History.Size - 1; i >= 0; i--)
    {
        if (Stricmp(History[i], command_line.c_str()) == 0)
        {
            free(History[i]);
            History.erase(History.begin() + i);
            break;
        }
    }

    History.push_back(Strdup(command_line.c_str()));

    vector<string> arguments = {};
    
    const char delim = ' ';
    split_str(command_line, delim, arguments);

    const char* tmp2 = new char[200];
    tmp2 = strtok(const_cast<char*>(command_line.c_str()), " ");
    command_line = tmp2;

    AddLog("$y#%s\n", command_line.c_str());

    auto command = commands.find(command_line);

    if (command != commands.end())
    {
        /* execute execuatable */
        
        if (commands[command_line](arguments) == 0)
        {
            ok();
        }

        else
        {
            not_ok();
        }
    }

    else if (Stricmp(command_line.c_str(), "clear") == 0 || Stricmp(command_line.c_str(), "cls") == 0)
    {
        FullClearLog();
    }

    else if (Stricmp(command_line.c_str(), "help") == 0)
    {
        AddLog("Commands:");
        for (int i = 0; i < Commands.Size; i++)
        {
            AddLog("- %s", Commands[i]);
        }

        ok();
    }

    else if (Stricmp(command_line.c_str(), "credits") == 0)
    {
        AddLog("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž, croatian's 'special' letters */
        AddLog("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui. If you have issue check our GitHub repo and report issue.");
        AddLog("If you know how to fix fell free to contribute it through pull requests on GitHub.");
        AddLog("LICENSE > ringwormGO General License 1.0 | (RGL) 2022");
        AddLog("REPO > https://github.com/ringwormGO-organization/Termi");

        ok();
    }

    else if (Stricmp(command_line.c_str(), "exit") == 0)
    {
        AddLog("Exiting...");
        exit(0);
    }

    else
    {
        AddLog("Unknown command: '%s'\n", command_line.c_str());
        not_ok();
    }

    arguments.clear();

    // On command input, we scroll to bottom even if AutoScroll==false
    ScrollToBottom = true;
    TypeTermi();
}

void Console::TypeTermi()
{
    AddLog("\nTermi> ");
}

int Console::TextEditCallback(ImGuiInputTextCallbackData* data)
{
    //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
    switch (data->EventFlag)
    {
        case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Example of TEXT COMPLETION

            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < Commands.Size; i++)
                if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                    candidates.push_back(Commands[i]);

            if (candidates.Size == 0)
            {
                // No match
                AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
                data->DeleteChars(0, data->BufTextLen);
            }
            else
            {
                // Multiple matches. Complete as much as we can..
                // So inputing "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                AddLog("Possible matches:\n");
                for (int i = 0; i < candidates.Size; i++)
                    AddLog("- %s\n", candidates[i]);
            }

            break;
        }
        case ImGuiInputTextFlags_CallbackHistory:
        {
            // Example of HISTORY
            const int prev_history_pos = HistoryPos;
            if (data->EventKey == ImGuiKey_UpArrow)
            {
                if (HistoryPos == -1)
                    HistoryPos = History.Size - 1;
                else if (HistoryPos > 0)
                    HistoryPos--;
            }
            else if (data->EventKey == ImGuiKey_DownArrow)
            {
                if (HistoryPos != -1)
                    if (++HistoryPos >= History.Size)
                        HistoryPos = -1;
            }

            // A better implementation would preserve the data on the current input line along with cursor position.
            if (prev_history_pos != HistoryPos)
            {
                const char* history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
                data->DeleteChars(0, data->BufTextLen);
                data->InsertChars(0, history_str);
            }
        }
    }
    return 0;
}

/* Draw context menu */
void Renderer::DrawMenu()
{
    if (BeginMenuBar())
    {
        if (BeginMenu(ChooseLanguage("terminal")))
        {
            if (MenuItem(ChooseLanguage("exit"), "Ctrl+X"))
            {
                exit(0);
            }

            ImGui::EndMenu();
        }

        if (BeginMenu(ChooseLanguage("edit")))
        {
            if (MenuItem(ChooseLanguage("font picker"), "Ctrl+F"))
            {
                if (isFont == false)
                {
                    Font(NULL);
                    isFont = true;
                }

                else
                {
                    isFont = false;
                }
            }

            Separator();

            if (MenuItem(ChooseLanguage("change theme"), "Ctrl+T"))
            {
                if (!isDarkTheme)
                {
                    StyleColorsLight();
                    isDarkTheme = true;
                }

                else
                {
                    StyleColorsDark();
                    isDarkTheme = false;
                }
            }

            Separator();

            if (MenuItem(ChooseLanguage("change language"), "Ctrl+L"))
            {
                if (!language_dialog)
                {
                    language_dialog = true;
                    ChooseLanguageDialog(NULL);
                }
            }

            ImGui::EndMenu();
        }

        if (BeginMenu(ChooseLanguage("about")))
        {
            if (MenuItem(ChooseLanguage("about termi")))
            {
                if (termi_dialog == false) 
                    termi_dialog = true;
                else 
                    termi_dialog = false;
            }

            if (MenuItem(ChooseLanguage("about imgui")))
            {
                if (imgui_dialog == false) 
                    imgui_dialog = true;
                else 
                    imgui_dialog = false;
            }

            ImGui::EndMenu();
        }

        EndMenuBar();
    }
}

/* Draw tabs */
void Renderer::DrawTab()
{
    
    static ImVector<int> active_tabs;
    static int next_tab_id = 0;
    if (next_tab_id == 0) // Initialize with some default tabs
        for (int i = 0; i < 1; i++)
            active_tabs.push_back(next_tab_id++);

    // TabItemButton() and Leading/Trailing flags are distinct features which we will demo together.
    // (It is possible to submit regular tabs with Leading/Trailing flags, or TabItemButton tabs without Leading/Trailing flags...
    // but they tend to make more sense together)
    static bool show_leading_button = false;
    static bool show_trailing_button = true;

    // Expose some other flags which are useful to showcase how they interact with Leading/Trailing tabs
    static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyResizeDown | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton;

    if (BeginTabBar("MyTabBar", tab_bar_flags))
    {
        // Demo Trailing Tabs: click the "+" button to add a new tab (in your app you may want to use a font icon instead of the "+")
        // Note that we submit it before the regular tabs, but because of the ImGuiTabItemFlags_Trailing flag it will always appear at the end.
        if (show_trailing_button)
            if (TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
                active_tabs.push_back(next_tab_id++); // Add new tab

        // Submit our regular tabs
        for (int n = 0; n < active_tabs.Size; )
        {
            bool open = true;
            char name[16] = "Termi";
            snprintf(name, IM_ARRAYSIZE(name), "%04d", active_tabs[n]);
            if (BeginTabItem(name, &open, ImGuiTabItemFlags_None))
            {
                DrawMenu();
                console.Draw();
                EndTabItem();
            }

            if (!open)
                active_tabs.erase(active_tabs.Data + n);
            else
                n++;
        }

        ImGui::EndTabBar();
    }
}

/* Font dialog */
void Renderer::Font(bool* p_open)
{
    ImGuiIO& io1 = GetIO();

    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(200, 200));
    if (!Begin("Font dialog", p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) isFont = false;
        EndPopup();
    }

    if (InputText("Enter name of font file", const_cast<char*>(font_name.c_str()), IM_ARRAYSIZE(const_cast<char*>(font_name.c_str())), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        //io1.Fonts->AddFontFromFileTTF(font.font_filename, font.size_pixels); todo
    }
    
    End();
}

/* Choose language function - return word on specified language */
const char* Renderer::ChooseLanguage(const char* word)
{
    if (language == "croatian")
    {
        if (word == "input") return Croatian::input;

        if (word == "terminal") return Croatian::terminal;
        if (word == "edit") return Croatian::edit;
        if (word == "about") return Croatian::about;

        if (word == "new tab") return Croatian::new_tab;
        if (word == "new profile") return Croatian::new_profile;
        if (word == "exit") return Croatian::exit_string;

        if (word == "font picker") return Croatian::font_picker;
        if (word == "change theme") return Croatian::change_theme;
        if (word == "change language") return Croatian::change_language;

        if (word == "about termi") return Croatian::about_termi;
        if (word == "about imgui") return Croatian::about_imgui;

        if (word == "settings") return Croatian::settings;
    }

    /* Default language - English */
    else
    {
        if (word == "input") return English::input;

        if (word == "terminal") return English::terminal;
        if (word == "edit") return English::edit;
        if (word == "about") return English::about;

        if (word == "new tab") return English::new_tab;
        if (word == "new profile") return English::new_profile;
        if (word == "exit") return English::exit_string;

        if (word == "font picker") return English::font_picker;
        if (word == "change theme") return English::change_theme;
        if (word == "change language") return English::change_language;

        if (word == "about termi") return English::about_termi;
        if (word == "about imgui") return English::about_imgui;
    }

    /* nothing matches */
    return "Unknown word";
}

/* Choose a language using dialog */
void Renderer::ChooseLanguageDialog(bool *p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(500, 500));
    if (!Begin("Language dialog", p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) language_dialog = false;
        EndPopup();
    }

    Text("Choose language / Odaberi jezik");
    Text(" "); /* empty space */

    if (Button("English (default)")) language = "english";
    if (Button("Croatian / Hrvatski")) language = "croatian";
    if (Button("Close window / Zatvori prozor")) language_dialog = false;

    End();
}

/* Dialog about Termi */
void Renderer::TermiDialog(bool* p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(400, 600));
    if (!Begin(ChooseLanguage("about termi"), p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) language_dialog = false;
        EndPopup();
    }

    Text("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž */
    Text("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui.\nIf you have issue check our GitHub repo and report issue.");
    Text("If you know how to fix fell free to contribute it through pull requests on GitHub.");
    Text("LICENSE > ringwormGO General License 1.0 | (RGL) 2022");
    Text("REPO > https://github.com/ringwormGO-organization/Termi");

    End();
}

/* Dialog about ImGui */
void Renderer::ImGuiDialog(bool* p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(400, 200));
    if (!Begin(ChooseLanguage("about imgui"), p_open))
    {
        End();
        return;
    }

    if (BeginPopupContextWindow())
    {
        if (Button("Close window")) language_dialog = false;
        EndPopup();
    }

    Text("ABOUT > Dear ImGui: Bloat-free Graphical User interface\nfor C++ with minimal dependencies.");
    Text("REPO > https://github.com/ocornut/imgui");

    End();
}

float Renderer::Settings(int id, float value)
{
    int temp_id = id;

    auto mode = ios::app | ios::in;
    string temp_str = "";

    if (!CheckFile("startup.txt"))
    {
        fstream file("startup.txt", mode);
        file << "none";
        file.close();
    }

    if (!CheckFile("width.txt"))
    {
        fstream file("width.txt", mode);
        file << 650;
        file.close();
    }

    if (!CheckFile("height.txt"))
    {
        fstream file("height.txt", mode);
        file << 650;
        file.close();
    }

    if (!CheckFile("font.txt"))
    {
        fstream file("font.txt", mode);
        file << "default";
        file.close();
    }

    if (!CheckFile("size.txt"))
    {
        fstream file("size.txt", mode);
        file << 16;
        file.close();
    }

    fstream startup("startup.txt", mode);
    fstream width("width.txt", mode);
    fstream height("height.txt", mode);
    fstream font("font.txt", mode);
    fstream font_size("size.txt", mode);

    fstream temp;

    switch (id)
    {
        case 0: /* startup command */
            while (getline(startup, temp_str))
            {
                startup_command = temp_str;
                startup.close();            
            }
            break;

        case 1: /* read width */
            while (getline(width, temp_str))
            {
                float result = stof(temp_str);
                width.close();
                return result;
            }
            break;

        case 2: /* read height */
            while (getline(height, temp_str))
            {
                float result = stof(temp_str);
                height.close();
                return result;
            }
            break;

        case 3: /* font name */
            while (getline(font, temp_str))
            {
                font_name = temp_str;
                font.close();
            }
            break;

        case 4: /* font size */
            while (getline(font_size, temp_str))
            {
                float result = stof(temp_str);
                font_size.close();
                return result;
            }
            break;

        case 5: /* write startup command */
            temp.open("temp.txt", mode);
            temp << startup_command;
            temp.close();
            remove("startup.txt");
            rename("temp.txt", "startup.txt");
            break;

        case 6: /* write width */
            temp.open("temp.txt", mode);
            temp << value;
            temp.close();
            remove("width.txt");
            rename("temp.txt", "width.txt");
            break;

        case 7: /* write height */
            temp.open("temp.txt", mode);
            temp << value;
            temp.close();
            remove("height.txt");
            rename("temp.txt", "height.txt");
            break;

        case 8: /* write font name*/
            temp.open("temp.txt", mode);
            temp << font_name;
            temp.close();
            remove("font.txt");
            rename("temp.txt", "font.txt");
            break;

        case 9: /* write font size */
            temp.open("temp.txt", mode);
            temp << value;
            temp.close();
            remove("size.txt");
            rename("temp.txt", "size.txt");
            break;
            
        default:
            console.AddLog("Invalid id %d!\n", id);
            console.AddLog(
            "ID list: \n%s%s%s%s%s%s%s%s%s%s%s",
            "0 - read startup command\n"
            "1 - read width\n",
            "2 - read height\n",
            "3 - set variable font_name to the font name\n",
            "4 - read font size\n",
            "---------------\n",
            "5 - write startup command\n",
            "6 - write width\n",
            "7 - write height\n",
            "8 - write font name\n",
            "9 - write font size\n"
            );
            return 1;
            break;
    }

    return 0;
}

/* Check if file exists */
bool Renderer::CheckFile(const char* name)
{
    fstream file;
    file.open(name);

    if (!file)
    {
        return false;
    }

    file.close();

    return true;
}

void main_code()
{
    /* ImGui window creation */
    Begin
    ("Termi",
        NULL,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_MenuBar |
        ImGuiInputTextFlags_AllowTabInput
    );

#ifdef PRINT_WHEN_WINDOW_IS_CREATED
    if (!alReadyPrinted)
    {
        cout << "Dear ImGui window is created.\n";
        alReadyPrinted = true;
    }
#endif

#ifdef PRINT_FPS
    SetCursorPosX(window_width + window_width / 200 - 100);
    TextColored(ImVec4(0, 0.88f, 0.73f, 1.00f), "(%.1f FPS)", GetIO().Framerate);
#endif

    /* Draw tabs and menu bar */
    render->DrawTab();

    /* Font dialog */
    if (isFont)
    {
        render->Font(NULL);
    }

    /* Language dialog */
    if (language_dialog)
    {
        render->ChooseLanguageDialog(NULL);
    }

    /* About Termi dialog */
    if (termi_dialog)
    {
        render->TermiDialog(NULL);
    }

    /* About ImGui dialog */
    if (imgui_dialog)
    {
        render->ImGuiDialog(NULL);
    }

    /* Get window width and height */
    window_width = GetWindowWidth();
    window_height = GetWindowHeight();

    /* End of window */
    End();
}
