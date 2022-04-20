/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and ImGUI rendering system
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: Main file for ImGUI
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && sudo make && ./Termi-OpenGL
*/

#include "imgui_code.hpp"

using namespace std;
using namespace ImGui;
using namespace nlohmann;

using namespace Translation;

#pragma GCC diagnostic ignored "-Wformat-security"

Console console;
Renderer* render;

json j;

/* Commands main code */

void neofetch(std::string argument, std::string argument2)
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
        info.OS = "GNU/Linux";
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
}

void openfile(std::string file, std::string argument)
{
    fstream my_file;
    my_file.open(file, ios::in);
    if (!my_file) 
    {
        console.AddLog("No such file %s!\n", file.c_str());
    }

    else 
    {
        std::string str; 
        while (getline(my_file, str))
        {
            console.AddLog("%s\n", str.c_str());
        }
    }
    console.AddLog("\n");
    my_file.close();
}

void list(std::string argument, std::string argument2)
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
}

void writefile(std::string file, std::string content)
{
    auto mode = ios::in;

    ofstream myfile;
    myfile.open(file, mode);
    myfile << content;
    myfile.close();
}

double calc(string op, double num1, double num2)
{
    if (!strcmp(op.c_str(), "+"))
    {
        return (num1 + num2);
    }

    else if(!strcmp(op.c_str(), "-"))
    {
        return (num1 - num2);
    }

    else if (!strcmp(op.c_str(), "*"))
    {
        return (num1 * num2);
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
            return (num1 / num2);
        }
    }

    else
    {
        console.AddLog("Invalid operator %s!\n", op.c_str());
        return 1;
    }

    return 1;
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
    Commands.push_back("calc");

    for (auto& x : commands)
    {
        Commands.push_back(x.first.c_str());
    }

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
        if (!Filter.PassFilter(item))
            continue;

        // Normally you would store more information in your item than just a string.
        // (e.g. make Items[] an array of structure, store color/type etc.)
        ImVec4 color;
        bool has_color = false;
        if (strstr(item, "[error]")) { color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
        else if (strncmp(item, "# ", 2) == 0) { color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
        if (has_color)
            PushStyleColor(ImGuiCol_Text, color);
        TextUnformatted(item);
        if (has_color)
            PopStyleColor();
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
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (InputText(render->ChooseLanguage("input"), InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
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

    string arg;
    string arg2;
    string arg3;
    bool _switch = false;
    bool __switch = false;
    bool ___switch = false;

    if (isStarting(command_line, "calc"))
    {
        char* tmp = new char[200];

        tmp = strtok(const_cast<char*>(command_line.c_str()), " ");

        while (tmp != NULL)
        {
            if (_switch)
            {
                if (__switch)
                {
                    if (___switch)
		            {
			            arg3 = tmp;
		            }

                    else
                    {
                        arg2 = tmp;
                        ___switch = true;
                    }
                }

                else
                {
                    arg = tmp;
                    __switch = true;
                }
            }

            else
            {
                command_line = tmp;
                _switch = true;
            }
            
            tmp = std::strtok(NULL, " , ");
        }
    }

    else
    {
        const char* tmp2 = new char[200];

        tmp2 = strtok(const_cast<char*>(command_line.c_str()), " ");

        while (tmp2 != NULL)
        {
            if (_switch)
            {
                if (__switch)
                {
                    arg2 = tmp2;
                }

                else
                {
                    arg = tmp2;
                    __switch = true;
                }
            }

            else
            {
                command_line = tmp2;
                _switch = true;
            }
            
            tmp2 = strtok(NULL, " , ");
        }
    }

    AddLog("# %s\n", command_line.c_str());

    auto command = commands.find(command_line);

    if (command != commands.end())
    {
        /* execute execuatable */
        commands[command_line](arg, arg2);
    }

    else if (Stricmp(command_line.c_str(), "calc") == 0)
    {
        console.AddLog("Result is: %e.\n", calc(arg, stod(arg2), stod(arg3)));
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
    }

    else if (Stricmp(command_line.c_str(), "credits") == 0)
    {
        AddLog("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž */
        AddLog("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui. If you have issue check our GitHub repo and report issue.");
        AddLog("If you know how to fix fell free to contribute it through pull requests on GitHub.");
        AddLog("LICENSE > BSD-3-Clause-License");
        AddLog("REPO > https://github.com/ringwormGO-organization/Termi");
    }

    else if (Stricmp(command_line.c_str(), "exit") == 0)
    {
        AddLog("Exiting...");
        exit(0);
    }

    else
    {
        AddLog("Unknown command: '%s'\n", command_line.c_str());
    }

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

/* Code for Renderer class */
/* PRIVATE INSTANCES OF Renderer class */
/* Draw new teminal tab */
void Renderer::DrawNewTab()
{

}

/* Check if file exists */
int Renderer::CheckFile(const char* name)
{
    fstream file;
    file.open(name);

    if (!file)
    {
        return 1;
    }

    file.close();

    return 0;
}

/* Draw context menu */
void Renderer::DrawContextMenu()
{
    if (BeginMenuBar())
    {
        if (BeginMenu(ChooseLanguage("terminal")))
        {
            if (MenuItem(ChooseLanguage("new tab"), "Ctrl+N"))
            {

            }

            if (MenuItem((ChooseLanguage("new profile")), "Ctrl+Shift+N"))
            {

            }

            Separator();

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

            Separator();

            if (MenuItem(ChooseLanguage("configure settings"), "Ctrl+S"))
            {
                Settings(j, 0);
            }

            if (MenuItem(ChooseLanguage("settings dialog"), "Ctrl+Shift+S"))
            {
                if (!settings_dialog)
                {
                    settings_dialog = true;
                    SettingsDialog(NULL);
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

    if (InputText("Enter name of font file", font_filename, IM_ARRAYSIZE(font_filename), ImGuiInputTextFlags_EnterReturnsTrue))
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
        if (word == "configure settings") return Croatian::configure_settings;
        if (word == "settings dialog") return Croatian::settings_dialog;
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

        if (word == "settings") return English::settings;
        if (word == "configure settings") return English::configure_settings;
        if (word == "settings dialog") return English::settings_dialog;
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
    Text("LICENSE > BSD-3-Clause-License");
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

template<typename T>
int Renderer::Settings(T, int id)
{
    auto mode = ios::app | ios::in;
    string temp_str = "";

    if (CheckFile("settings.json") != 0)
    {
        fstream json_file_new("settings.json", mode);
    }

    else /* temporary */
    {
        remove("settings.json");
    }

    fstream json_file("settings.json", mode);

    switch (id)
    {
        case 0:
            /* set up all defaults and read file */

            j["width"] = window_width;
            j["height"] = window_height;
            json_file << j;
            break;

        case 1:
            /* read resulution */
            break;
            

        default:
            console.AddLog("Invalid id %d!\n", id);
            break;
    }

    json_file.close();
    return 0;
}

void Renderer::SettingsDialog(bool* p_open)
{
    SetWindowPos(ImVec2(200, 200));
    SetWindowSize(ImVec2(400, 600));
    if (!Begin(ChooseLanguage("settings dialog"), p_open))
    {
        language_dialog = false;
        End();
        return;
    }

    int id = 0;

    if (InputInt("Enter id: ", &id, 1, 100, ImGuiInputTextFlags_EnterReturnsTrue))
    {
        Settings(j, id);
    }

    language_dialog = false;
    End();
}

void main_code()
{
    /* ImGUI window creation */
    SetNextWindowPos(ImVec2(pos_x, pos_y));
    SetNextWindowSize(ImVec2(window_width, window_height));
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
        cout << "ImGui window is created.\n";
        alReadyPrinted = true;
    }
#endif

#ifdef PRINT_FPS
    SetCursorPosX(window_width + window_width / 200 - 100);
    TextColored(ImVec4(0, 0.88f, 0.73f, 1.00f), "(%.1f FPS)", GetIO().Framerate);
#endif

    /* Draw menu bar */
    render->DrawContextMenu();

    /* Draw console */
    console.Draw();

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

    /* Settings dialog */
    if (settings_dialog)
    {
        render->SettingsDialog(NULL);
    }

    /* Get window width and height */
    window_width = GetWindowWidth();
    window_height = GetWindowHeight();


    /* End of window */
    End();
}
