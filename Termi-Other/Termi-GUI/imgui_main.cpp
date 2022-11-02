/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file for Dear ImGui
*/

#include "imgui_code.hpp"

#pragma GCC diagnostic ignored "-Wformat-security"
#pragma GCC diagnostic ignored "-Wreturn-type"
#pragma GCC diagnostic ignored "-Wstringop-overflow="

void ColorfulText(const std::string& text, const std::list<std::pair<char, ImVec4>>& colors) 
{
    auto p = ImGui::GetCursorScreenPos();
    const auto first_px = p.x, first_py = p.y;
    auto im_colors = ImGui::GetStyle().Colors;
    const auto default_color = im_colors[ImGuiCol_Text];
    std::string temp_str;
    struct text_t 
    {
        ImVec4 color;
        std::string text;
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
        std::list<std::string> lines;
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
            ImGui::Text(j.c_str());
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
            p.x += ImGui::CalcTextSize(last.c_str()).x;
    };
    im_colors[ImGuiCol_Text] = default_color;
    ImGui::Dummy({ max_x - p.x, p.y - first_py });
};

void split_str(std::string const &str, const char delim, std::vector<std::string> &out)  
{  
    /* create a stream from the string */  
    std::stringstream s(str);  
        
    std::string s2;  
    while (getline (s, s2, delim))  
    {  
        out.push_back(s2); /* store the string in s2 */  
    }
}

std::vector<std::pair<Renderer*, Console*>> vprender;
int console_id;

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

    std::sort(Commands.begin(), Commands.end());

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

void Console::LoadSO(std::vector<std::string>& vect, std::string function)
{
    void *handle;
    void (*func)(const std::vector<std::string>&);
    char *error;

    handle = dlopen ("libTermi-Commands.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        puts(" ");
        exit(1);
    }

    func = dlsym(handle, function.c_str());
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    (*func)(vect);
    dlclose(handle);
}

int Console::LoadThirdParty(const char* path, const char* function, const char* value)
{
    void *handle;
    void (*func)(const char*);
    char *error;

    handle = dlopen (path, RTLD_LAZY);
    if (!handle) {
        printf("%s\n", dlerror());
        printf("-------------\n");
        return 1;
    }

    func = dlsym(handle, function);
    if ((error = dlerror()) != NULL)  {
        printf("%s\n", error);
        printf("-------------\n");
        return 1;
    }

    (*func)(value);
    dlclose(handle);

    return 0;
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

    if (Items.size() + 1 == 4000)
    {
        Items.erase(Items.begin());
    }

    Items.push_back(Strdup(buf));
}

void Console::Draw()
{
    // TODO: display items starting from the bottom

    // Reserve enough left-over height for 1 separator + 1 input text
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Selectable("Clear")) ClearLog();
        if (ImGui::Selectable("Copy")) Copy = true;
        ImGui::EndPopup();
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
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
    if (Copy)
        ImGui::LogToClipboard();
    for (int i = 0; i < Items.Size; i++)
    {
        const char* item = Items[i];
        ColorfulText(item, {{'w', white}, {'b', blue}, {'d', grey}, {'l', lgrey}, {'g', green}, {'m', lime}, {'y', yellow}, {'p', purple}, {'r', red}, {'o', orange}});
    }
    if (Copy)
        ImGui::LogFinish();

    if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
        ImGui::SetScrollHereY(1.0f);
    ScrollToBottom = false;

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Separator();

    bool reclaim_focus = false;
    if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0) && !help_focus)
    {
        ImGui::SetKeyboardFocusHere(0);
        help_focus = true;
    }

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText(cwd, InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
    {
        s = InputBuf;
        Strtrim(s);
        if (s[0])
            ExecCommand(s);
        strcpy(s, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
}

void Console::ExecCommand(std::string command_line, ...)
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

    if (History.size() + 1 == 4000)
    {
        History.erase(History.begin());
    }

    History.push_back(Strdup(command_line.c_str()));

    std::vector<std::string> arguments = {};
    const char delim = ' ';
    split_str(command_line, delim, arguments);
    command_line = const_cast<char*>(strtok(const_cast<char*>(command_line.c_str()), " "));

    AddLog("$y#%s\n", command_line.c_str());
    auto command = commands.find(command_line);

    if (command != commands.end())
    {
        auto result = commands.find(command_line);
        LoadSO(arguments, result->second.c_str());
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

        AddLog("$g\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Successfully executed!");
    }

    else if (Stricmp(command_line.c_str(), "credits") == 0)
    {
        AddLog("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž, croatian's 'special' letters */
        AddLog("ABOUT > A powerful independent terminal made in C++ which use OpenGL and Dear ImGui. If you have issue check our GitHub repo and report issue.");
        AddLog("If you know how to fix fell free to contribute it through pull requests on GitHub.");
        AddLog("LICENSE > ringwormGO General License 1.0 | (RGL) 2022");
        AddLog("REPO > https://github.com/ringwormGO-organization/Termi");

        AddLog("$g\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Successfully executed!");
    }

    else if (Stricmp(command_line.c_str(), "exit") == 0)
    {
        AddLog("Exiting...");
        exit(0);
    }

    else
    {
        std::string choice, path, funciton, params;

        std::cout << "Do you want to load command or application from third party .so file [y/n]: ";
        std::cin >> choice;

        if (choice == "y")
        {
            std::cout << "Enter a path of .so file: ";
            std::cin >> path;

            std::cout << "Enter a name of function: ";
            std::cin >> funciton;

            std::cout << "Enter arguments (one string at the time because of Rust compatability): ";
            std::cin >> params;

            LoadThirdParty(path.c_str(), funciton.c_str(), params.c_str());
        }

        else
        {
            std::cout << "\n";
            AddLog("Unknown command: '%s'\n", command_line.c_str());

            /* Blue - user error | Red - system error */
            AddLog("$b\t\t\t\t\t\t\t\t\t\t\t\t Not successfully executed, user error!");
        }
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
void Renderer::DrawMenu(Vars* vars)
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu(ChooseLanguage(vars, 1)))
        {
            if (ImGui::MenuItem(ChooseLanguage(vars, 6), "Ctrl+X"))
            {
                exit(0);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ChooseLanguage(vars, 2)))
        {
            if (ImGui::MenuItem(ChooseLanguage(vars, 7), "Ctrl+F"))
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

            ImGui::Separator();

            if (ImGui::MenuItem(ChooseLanguage(vars, 8), "Ctrl+T"))
            {
                if (!isDarkTheme)
                {
                    ImGui::StyleColorsLight();
                    isDarkTheme = true;
                }

                else
                {
                    ImGui::StyleColorsDark();
                    isDarkTheme = false;
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem(ChooseLanguage(vars, 9), "Ctrl+L"))
            {
                if (!language_dialog)
                {
                    language_dialog = true;
                    ChooseLanguageDialog(vars, NULL);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ChooseLanguage(vars, 3)))
        {
            if (ImGui::MenuItem(ChooseLanguage(vars, 10)))
            {
                if (termi_dialog == false) 
                    termi_dialog = true;
                else 
                    termi_dialog = false;
            }

            if (ImGui::MenuItem(ChooseLanguage(vars, 11)))
            {
                if (imgui_dialog == false) 
                    imgui_dialog = true;
                else 
                    imgui_dialog = false;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

/* Font dialog */
void Renderer::Font(bool* p_open)
{
    ImGuiIO& io1 = ImGui::GetIO();

    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(200, 200));
    if (!ImGui::Begin("Font dialog", p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window")) isFont = false;
        ImGui::EndPopup();
    }

    if (ImGui::InputText("Enter name of font file", const_cast<char*>(font_name.c_str()), IM_ARRAYSIZE(const_cast<char*>(font_name.c_str())), ImGuiInputTextFlags_EnterReturnsTrue))
    {
        //io1.Fonts->AddFontFromFileTTF(font.font_filename, font.size_pixels); todo
    }
    
    ImGui::End();
}

/* Choose language function - return word on specified language */
const char* Renderer::ChooseLanguage(Vars* vars, int id)
{
    if (vars->language == "english")
    {
        return Translation::English.at(id).c_str();
    }

    else if (vars->language == "croatian")
    {
        return Translation::Croatian.at(id).c_str();
    }

    else if (vars->language == "vietnamese") 
    {
        return Translation::Vietnamese.at(id).c_str();
    }

    /* nothing matches */
    return "Unknown word";
}

/* Choose a language using dialog */
void Renderer::ChooseLanguageDialog(Vars* vars, bool *p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(500, 500));
    if (!ImGui::Begin("Language dialog", p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window")) language_dialog = false;
        ImGui::EndPopup();
    }

    ImGui::Text("Choose language / Odaberi jezik");
    ImGui::Text(" "); /* empty space */

    if (ImGui::Button("English (default)")) vars->language = "english";
    if (ImGui::Button("Croatian / Hrvatski")) vars->language = "croatian";
    if (ImGui::Button("Vietnamese / Tiếng Việt")) vars->language = "vietnamese";
    /* if (ImGui::Button("Vietnamese / Tieng Viet")) vars->language = "vietnamese"; */
    if (ImGui::Button("X")) language_dialog = false;

    ImGui::End();
}

/* Dialog about Termi */
void Renderer::TermiDialog(Vars* vars, bool* p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(400, 600));
    if (!ImGui::Begin(ChooseLanguage(vars, 10), p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window")) language_dialog = false;
        ImGui::EndPopup();
    }

    ImGui::Text("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic"); /* todo: font which support č, ć, š, đ and ž */
    ImGui::Text("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui.\nIf you have issue check our GitHub repo and report issue.");
    ImGui::Text("If you know how to fix fell free to contribute it through pull requests on GitHub.");
    ImGui::Text("LICENSE > ringwormGO General License 1.0 | (RGL) 2022");
    ImGui::Text("REPO > https://github.com/ringwormGO-organization/Termi");

    ImGui::End();
}

/* Dialog about ImGui */
void Renderer::ImGuiDialog(Vars* vars, bool* p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(400, 200));
    if (!ImGui::Begin(ChooseLanguage(vars, 11), p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window")) language_dialog = false;
        ImGui::EndPopup();
    }

    ImGui::Text("ABOUT > Dear ImGui: Bloat-free Graphical User interface\nfor C++ with minimal dependencies.");
    ImGui::Text("REPO > https://github.com/ocornut/imgui");

    ImGui::End();
}

int Renderer::Settings(int id, float value)
{
    char user[64];
    getlogin_r(user, 64);

    std::string folder_path = "/home/" + std::string(user) + "/.config/termi/";
    std::string file_path = folder_path + "settings.json";
    std::string default_json = "{\n\"startup_command\": \"none\",\n\"width\": 650,\n\"height\": 650,\n\"font_name\": \"none\",\n\"font_size\": 16\n}\n";

    auto mode = std::ios::app | std::ios::in;
    std::string temp_str = "";

    if (!std::filesystem::exists(folder_path) && !std::filesystem::is_directory(folder_path))
    {
        mkdir(folder_path.c_str(), 0777);
    }

    if (!CheckFile(file_path.c_str()))
    {
        std::fstream file(file_path, mode);
        file << default_json;
        file.close();
    }

    FILE* file = fopen(file_path.c_str(), "r");
    if (file == NULL)
    {
        std::cout << "File '" << file_path << "' not found, returning default settings!\n";

        switch (id)
        {
            case 0: /* startup command */
                startup_command = "none";
                break;

            case 1: /* read width */
                return 650;
                break;

            case 2: /* read height */
                return 650;
                break;

            case 3: /* font name */
                font_name = "none";
                break;

            case 4: /* font size */
                return 16;
                break;
                
            default:
                vprender[console_id].second->AddLog("Invalid id %d!\n", id);
                vprender[console_id].second->AddLog(
                "ID list: \n%s%s%s%s%s%s%s%s%s%s%s",
                "0 - read startup command\n"
                "1 - read width\n",
                "2 - read height\n",
                "3 - set variable font_name to the font name\n",
                "4 - read font size\n"
                );
                return 1;
                break;
        }
        return 1;
    }

    char buffer[1024];

    fread(buffer, 1024, 1, file);
    fclose(file);
    
    struct json_object* parsed_json;
    struct json_object* j_startup_command;
    struct json_object* j_width;
    struct json_object* j_height;
    struct json_object* j_font_name;
    struct json_object* j_font_size;

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "startup_command", &j_startup_command);
    json_object_object_get_ex(parsed_json, "width", &j_width);
    json_object_object_get_ex(parsed_json, "height", &j_height);
    json_object_object_get_ex(parsed_json, "font_name", &j_font_name);
    json_object_object_get_ex(parsed_json, "font_size", &j_font_size);

    switch (id)
    {
        case 0: /* startup command */
            startup_command = std::string(json_object_get_string(j_startup_command));
            break;

        case 1: /* read width */
            return json_object_get_int(j_width);
            break;

        case 2: /* read height */
            return json_object_get_int(j_height);
            break;

        case 3: /* font name */
            font_name = std::string(json_object_get_string(j_font_name));
            break;

        case 4: /* font size */
            return json_object_get_int(j_font_size);
            break;
            
        default:
            vprender[console_id].second->AddLog("Invalid id %d!\n", id);
            vprender[console_id].second->AddLog(
            "ID list: \n%s%s%s%s%s%s%s%s%s%s%s",
            "0 - read startup command\n"
            "1 - read width\n",
            "2 - read height\n",
            "3 - set variable font_name to the font name\n",
            "4 - read font size\n"
            );
            return 1;
            break;
    }

    return 0;
}

/* Check if file exists */
bool Renderer::CheckFile(const char* name)
{
    std::fstream file;
    file.open(name);

    if (!file)
    {
        return false;
    }

    file.close();
    return true;
}

/* Function which draws tabs */
void DrawTab(Vars* vars)
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

    if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
    {
        // Demo Trailing Tabs: click the "+" button to add a new tab (in your app you may want to use a font icon instead of the "+")
        // Note that we submit it before the regular tabs, but because of the ImGuiTabItemFlags_Trailing flag it will always appear at the end.
        if (show_trailing_button)
            if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
                active_tabs.push_back(next_tab_id++); // Add new tab

        // Submit our regular tabs
        for (int n = 0; n < active_tabs.Size; )
        {
            bool open = true;
            char name[16] = "Termi";
            snprintf(name, IM_ARRAYSIZE(name), "%04d", active_tabs[n]);
            if (ImGui::BeginTabItem(name, &open, ImGuiTabItemFlags_None))
            {
                if (strcmp(name, "0000") == 0)
                {
                    console_id = 0;
                    vprender[0].first->DrawMenu(vars);
                    vprender[0].second->Draw();
                    ImGui::EndTabItem();
                }

                else
                {
                    console_id = atoi(name);
                    vprender[console_id].first->DrawMenu(vars);
                    vprender[console_id].second->Draw();
                }
            }

            if (!open)
                active_tabs.erase(active_tabs.Data + n);
            else
                n++;
        }

        ImGui::EndTabBar();
    }
}

void main_code(Vars* vars)
{
    /* ImGui window creation */
    ImGui::Begin
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
        std::cout << "Dear ImGui window is created.\n";
        alReadyPrinted = true;
    }
#endif

#ifdef PRINT_FPS
    ImGui::SetCursorPosX(window_width + window_width / 200 - 200);
    ImGui::TextColored(ImVec4(0, 0.88f, 0.73f, 1.00f), "(%.3f ms/frame, %.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
#endif

    vprender.push_back(std::make_pair(new Renderer(), new Console()));

    /* Draw tabs and menu bar */
    DrawTab(vars);

    /* Font dialog */
    if (isFont)
    {
        vprender[0].first->Font(NULL);
    }

    /* Language dialog */
    if (language_dialog)
    {
        vprender[0].first->ChooseLanguageDialog(vars, NULL);
    }

    /* About Termi dialog */
    if (termi_dialog)
    {
        vprender[0].first->TermiDialog(vars, NULL);
    }

    /* About ImGui dialog */
    if (imgui_dialog)
    {
        vprender[0].first->ImGuiDialog(vars, NULL);
    }

    /* Get window width and height */
    window_width = ImGui::GetWindowWidth();
    window_height = ImGui::GetWindowHeight();

    /* End of window */
    ImGui::End();

    /*for (auto x : vprender)
    {
        delete x.first;
        delete x.second;
    }*/
}

void AddLog(const char* fmt, ...)
{
    vprender[console_id].second->AddLog(fmt);
}
