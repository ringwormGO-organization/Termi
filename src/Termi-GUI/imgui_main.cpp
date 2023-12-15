/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Main file for Dear ImGui
 */

#include "imgui_code.hpp"

#if defined _WIN32 || defined _WIN64
    #pragma warning(disable : 4996)    
#endif

/**
 * Function which colors text
 * Credits: https://github.com/ocornut/imgui/issues/902#issuecomment-1103072284
 * @param text - string to colorize
 * @param colors - std::pair of letter representing color and ImVec4 representing color values in 4D vector
 */
void ColorfulText(const std::string &text, const std::list<std::pair<char, ImVec4>> &colors)
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

    for (const auto &i : text)
    {
        if (color_time)
        {
            const auto &f = std::find_if(colors.begin(), colors.end(), [i](const auto &v)
                                         { return v.first == i; });
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
            if (!temp_str.empty())
            {
                texts.push_back({last_color, temp_str});
                temp_str.clear();
            };
            break;
        default:
            temp_str += i;
        };
    };

    if (!temp_str.empty())
    {
        texts.push_back({last_color, temp_str});
        temp_str.clear();
    };

    float max_x = p.x;
    for (const auto &i : texts)
    {
        im_colors[ImGuiCol_Text] = i.color;
        std::list<std::string> lines;
        temp_str.clear();
        for (const auto &lc : i.text)
        {
            if (lc == '\n')
            {
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
        for (const auto &j : lines)
        {
            ImGui::Text(j.c_str());
            p.y += 15.f;
            last_px = p.x;
            max_x = (max_x < last_px) ? last_px : max_x;
            p.x = first_px;
        };
        const auto &last = lines.back();
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
    ImGui::Dummy({max_x - p.x, p.y - first_py});
};

/**
 * Function to split the given string using the getline() function
 * Credits: https://www.javatpoint.com/how-to-split-strings-in-cpp
 * @param str - string
 * @param delim - char with which we separate strings
 * @param out - vector which has seperated strings
 */
void split_str(std::string const &str, const char delim, std::vector<std::string> &out)
{
    /* create a stream from the string */
    std::stringstream s(str);

    std::string s2;
    while (getline(s, s2, delim))
    {
        out.push_back(s2); /* store the string in s2 */
    }
}

/** Vector holding std::tuple type representing renderer, console and variable of all tabs
 * @param _T1 - pair of Renderer and Console
 * @param _T2 - pair of Vars and nullptr, I had to put that nullptr so I can compile code but otherwise you should not use it
 */
std::vector<std::tuple<std::unique_ptr<Renderer>, std::unique_ptr<Console>, std::unique_ptr<Vars>>> vpprender;

/**
 * Current vpprender element in use
 */
int vpprender_id;

/*
 * Console class - everything for drawing and managing console
 * Code for functions here
 * Code from imgui_demo.cpp
 */
Console::Console()
{
    if (Settings(6) == 0)
    {
        FullClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        Commands.push_back("help");
        Commands.push_back("credits");
        Commands.push_back("clear");
        Commands.push_back("cls");
        Commands.push_back("loadtp");
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

    else
    {
        bool open = true;
        ImGui::Begin("Terminal", &open);

        ImGui::SetKeyboardFocusHere();

        static char str_hold[1024] = "Termi> ";

        /* The textbox flags.This will make `InputTextMultiline` return true when[Enter] is pressed */
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CtrlEnterForNewLine;
        if (ImGui::InputTextMultiline("", str_hold, 1024, ImGui::GetWindowSize(), flags)) {
            /* The code in this if - statement only executes when[Enter] is pressed */
            strcat(str_hold, "\nTermi> ");
            ImGui::SetKeyboardFocusHere();
        }

        ImGui::End();
    }
}

Console::~Console()
{
    if (Settings(6) == 0)
    {
        FullClearLog();
        for (int i = 0; i < History.Size; i++)
            free(History[i]);
    }
}

void Console::LoadDynamicLibrary(std::vector<std::string> &vect, std::string function)
{
    #if defined _WIN32 || defined _WIN64
        typedef int(__cdecl* FUNC)(const std::vector<std::string>&);

        HINSTANCE hinstLib;
        FUNC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.
        hinstLib = LoadLibrary(TEXT("Termi-Commands.dll"));

        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (FUNC)GetProcAddress(hinstLib, function.c_str());

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(vect);
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Failed to run function from executable!\n");
        }
    #elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
        __NetBSD__
        void *handle;
        void (*func)(const std::vector<std::string> &);
        char *error;

        handle = dlopen("libTermi-Commands.so", RTLD_LAZY);
        if (!handle)
        {
            fputs(dlerror(), stderr);
            puts(" ");
            exit(1);
        }

        func = reinterpret_cast<void (*)(const std::vector<std::string> &)>(dlsym(handle, function.c_str()));
        if ((error = dlerror()) != NULL)
        {
            fputs(error, stderr);
            exit(1);
        }

        (*func)(vect);
        dlclose(handle); 
    #endif
}

int Console::LoadThirdParty(const char *path, const char *function, const char *value)
{
    #if defined _WIN32 || defined _WIN64
        typedef void(__cdecl* THIRD_PARTY)(const char*);

        HINSTANCE hinstLib;
        THIRD_PARTY ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module.
        hinstLib = LoadLibrary((LPCSTR)path);

        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (THIRD_PARTY)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(value);
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Failed to run function from executable!\n\n");
        }
    #elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
        __NetBSD__
        void *handle;
        void (*func)(const char *);
        char *error;

        handle = dlopen(path, RTLD_LAZY);
        if (!handle)
        {
            printf("%s\n", dlerror());
            printf("-------------\n");
            return 1;
        }

        func = reinterpret_cast<void (*)(const char *)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)
        {
            printf("%s\n", error);
            printf("-------------\n");
            return 1;
        }

        (*func)(value);
        dlclose(handle);
    #endif

    return 0;
}

void Console::ClearLog()
{
    if (Settings(6) == 0)
    {
        for (int i = 0; i < Items.Size; i++)
            free(Items[i]);
        Items.clear();

        TypeTermi();
    }
}

void Console::FullClearLog()
{
    if (Settings(6) == 0)
    { 
        for (int i = 0; i < Items.Size; i++)
            free(Items[i]);
        Items.clear();
    }
}

void Console::AddLog(const char *fmt, ...)
{
    if (Settings(6) == 0)
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
}

void Console::Draw()
{
    if (Settings(6) == 0)
    {
        // TODO: display items starting from the bottom

        // Reserve enough left-over height for 1 separator + 1 input text
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear"))
                ClearLog();
            if (ImGui::Selectable("Copy"))
                Copy = true;
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
            ColorfulText(item, { {'w', white}, {'b', blue}, {'d', grey}, {'l', lgrey}, {'g', green}, {'m', lime}, {'y', yellow}, {'p', purple}, {'r', red}, {'o', orange} });
        }
        if (Copy)
            ImGui::LogFinish();

        if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
            ImGui::SetScrollHereY(1.0f);
        ScrollToBottom = false;

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        if (std::get<2>(vpprender[vpprender_id])->server)
        {
            
        }

        bool reclaim_focus = false;
        if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0) && !std::get<2>(vpprender[vpprender_id])->alReadyFocusOnInputBar)
        {
            ImGui::SetKeyboardFocusHere(0);
            std::get<2>(vpprender[vpprender_id])->alReadyFocusOnInputBar = true;
        }

        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));

        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
        if (ImGui::InputText(cwd, InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
        {
            s = InputBuf;
            Strtrim(s);

            if (s[0])
            {
                ExecCommand(s);
            }

            strcpy(s, "");
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
    }

    else
    {
        bool reclaim_focus = false;

        char cwd[PATH_MAX];
        getcwd(cwd, sizeof(cwd));

        static char str_hold[1024] = "Termi> ";

        /* The textbox flags.This will make `InputTextMultiline` return true when[Enter] is pressed */
        ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CtrlEnterForNewLine | ImGuiInputTextFlags_AutoSelectAll;
        if (ImGui::InputTextMultiline("", str_hold, 1024, ImGui::GetWindowSize(), flags)) {
            /* The code in this if - statement only executes when[Enter] is pressed */
            strcat(str_hold, "\nTermi> ");
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
    }
}

void Console::ExecCommand(std::string command_line, ...)
{
    if (Settings(6) == 0)
    {
        /**
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
            LoadDynamicLibrary(arguments, result->second.c_str());
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
            AddLog("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic");
            AddLog("ABOUT > A powerful independent terminal made in C++ which use OpenGL and Dear ImGui. If you have issue check our GitHub repo and report issue.");
            AddLog("If you know how to fix fell free to contribute it through pull requests on GitHub.");
            AddLog("LICENSE > ringwormGO General License 1.0 | (RGL) 2022");
            AddLog("REPO > https://github.com/ringwormGO-organization/Termi");

            AddLog("$g\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t Successfully executed!");
        }

        else if (Stricmp(command_line.c_str(), "loadtp") == 0)
        {
            if (arguments.size() < 3)
            {
                AddLog("No enough arguments!\n");
                AddLog("$b\t\t\t\t\t\t\t\t\t\t\t\t Not successfully executed, user error!");

                goto end;
            }

            std::string argument;
            for (size_t i = 0; i < arguments.size(); i++)
            {
                if (i < 3)
                {
                    continue;
                }

                else
                {
                    argument += arguments[i];
                    argument += " ";
                }
            }

            LoadThirdParty(arguments[1].c_str(), arguments[2].c_str(), argument.c_str());
        }

        else if (Stricmp(command_line.c_str(), "exit") == 0)
        {
            AddLog("Exiting...");
            exit(0);
        }

        else
        {
            AddLog("Unknown command: '%s'\n", command_line.c_str());

            /* Blue - user error | Red - system error */
            AddLog("$b\t\t\t\t\t\t\t\t\t\t\t\t Not successfully executed, user error!");
        }

    end:
        arguments.clear();

        // On command input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
        TypeTermi();
    }
}

void Console::TypeTermi()
{
    if (Settings(6) == 0)
    {
        AddLog("\nTermi> ");
    }
}

int Console::TextEditCallback(ImGuiInputTextCallbackData *data)
{
    if (Settings(6) == 0)
    {
        // AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
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
}

/* Draw context menu */
void Renderer::DrawMenu(ImGuiStyle& style)
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu(ChooseLanguage(1)))
        {
            if (ImGui::MenuItem(ChooseLanguage(12)) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                #if __linux
                    if (!std::get<2>(vpprender[vpprender_id])->server) /* server is off */
                    {
                        std::get<2>(vpprender[vpprender_id])->server = true;

                        std::thread server(CreateServer);
                        server.detach();
                    }

                    else /* server is on */
                    {
                        std::get<2>(vpprender[vpprender_id])->server = false;
                    }
                #endif
            }

            ImGui::Separator();

            if (ImGui::MenuItem(ChooseLanguage(6)) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                exit(0);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ChooseLanguage(2)))
        {
            if (ImGui::MenuItem(ChooseLanguage(7)) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (std::get<2>(vpprender[vpprender_id])->isDarkTheme)
                {
                    ImGui::StyleColorsLight();
                    std::get<2>(vpprender[vpprender_id])->isDarkTheme = false;
                }

                else
                {
                    ImGui::StyleColorsDark();
                    std::get<2>(vpprender[vpprender_id])->isDarkTheme = true;
                }
            }

            if (ImGui::MenuItem(ChooseLanguage(14)))
            {
                again:
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> dist(0, std::get<2>(vpprender[vpprender_id])->themes.size() - 1);

                if (std::get<2>(vpprender[vpprender_id])->theme == std::get<2>(vpprender[vpprender_id])->themes.at(static_cast<int>(dist(rng))))
                {
                    goto again;
                }

                std::get<2>(vpprender[vpprender_id])->theme = std::get<2>(vpprender[vpprender_id])->themes.at(static_cast<int>(dist(rng)));

                if (std::get<2>(vpprender[vpprender_id])->theme == "dark_red")
                {
                    style.Colors[ImGuiCol_WindowBg] = ImColor(84, 3, 34);
                }

                else if (std::get<2>(vpprender[vpprender_id])->theme == "aqua")
                {
                    style.Colors[ImGuiCol_WindowBg] = ImColor(0, 255, 255);
                }

                else if (std::get<2>(vpprender[vpprender_id])->theme == "some_yellow")
                {
                    style.Colors[ImGuiCol_WindowBg] = ImColor(204, 163, 80);
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem(ChooseLanguage(8)) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (!std::get<2>(vpprender[vpprender_id])->language_dialog)
                {
                    std::get<2>(vpprender[vpprender_id])->language_dialog = true;
                    ChooseLanguageDialog(NULL);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ChooseLanguage(3)))
        {
            if (ImGui::MenuItem(ChooseLanguage(9)) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (std::get<2>(vpprender[vpprender_id])->termi_dialog == false)
                    std::get<2>(vpprender[vpprender_id])->termi_dialog = true;
                else
                    std::get<2>(vpprender[vpprender_id])->termi_dialog = false;
            }

            if (ImGui::MenuItem(ChooseLanguage(10)) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (std::get<2>(vpprender[vpprender_id])->imgui_dialog == false)
                    std::get<2>(vpprender[vpprender_id])->imgui_dialog = true;
                else
                    std::get<2>(vpprender[vpprender_id])->imgui_dialog = false;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

/* Choose language function - return word on specified language */
const char *Renderer::ChooseLanguage(int id)
{
    if (std::get<2>(vpprender[vpprender_id])->language == "english")
    {
        return Translation::English.at(id).c_str();
    }

    else if (std::get<2>(vpprender[vpprender_id])->language == "croatian")
    {
        return Translation::Croatian.at(id).c_str();
    }

    else if (std::get<2>(vpprender[vpprender_id])->language == "vietnamese")
    {
        return Translation::Vietnamese.at(id).c_str();
    }

    /* nothing matches */
    return "Unknown word";
}

/* Choose a language using dialog */
void Renderer::ChooseLanguageDialog(bool *p_open)
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
        if (ImGui::Button("Close window"))
        {
            std::get<2>(vpprender[vpprender_id])->language_dialog = false;
        }

        ImGui::EndPopup();
    }

    ImGui::Text("Choose language / Odaberi jezik");
    ImGui::Text(" "); /* empty space */

    if (ImGui::Button("English (default)") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        std::get<2>(vpprender[vpprender_id])->language = "english";
    }

    if (ImGui::Button("Croatian / Hrvatski") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        std::get<2>(vpprender[vpprender_id])->language = "croatian";
    }

    if (ImGui::Button("Vietnamese / Tiếng Việt") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        std::get<2>(vpprender[vpprender_id])->language = "vietnamese";
    }

    /* if (ImGui::Button("Vietnamese / Tieng Viet")) std::get<2>(vpprender[vpprender_id])->language = "vietnamese"; */

    if (ImGui::Button("X") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        std::get<2>(vpprender[vpprender_id])->language_dialog = false;
    }

    ImGui::End();
}

/* Dialog about Termi */
void Renderer::TermiDialog(bool *p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(500, 700));
    if (!ImGui::Begin(ChooseLanguage(9), p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window"))
        {
            std::get<2>(vpprender[vpprender_id])->termi_dialog = false;
        }

        ImGui::EndPopup();
    }

    if (ImGui::Button("X") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        std::get<2>(vpprender[vpprender_id])->termi_dialog = false;
    }

    ImGui::Text("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic");
    ImGui::Text("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui.\nIf you have issue check our GitHub repo and report issue.");
    ImGui::Text("If you know how to fix fell free to contribute it through pull requests on GitHub.");
    ImGui::Text("LICENSE > ringwormGO General License 1.0 | (RGL) 2022");
    ImGui::Text("REPO > https://github.com/ringwormGO-organization/Termi");

    ImGui::End();
}

/* Dialog about ImGui */
void Renderer::ImGuiDialog(bool *p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(500, 300));
    if (!ImGui::Begin(ChooseLanguage(10), p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window"))
        {
            std::get<2>(vpprender[vpprender_id])->imgui_dialog = false;
        }

        ImGui::EndPopup();
    }

    if (ImGui::Button("X") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        std::get<2>(vpprender[vpprender_id])->imgui_dialog = false;
    }

    ImGui::Text("ABOUT > Dear ImGui: Bloat-free Graphical User interface\nfor C++ with minimal dependencies.");
    ImGui::Text("REPO > https://github.com/ocornut/imgui");

    ImGui::End();
}

int Renderer::Settings(int id)
{
    #if defined _WIN32 || defined _WIN64
        std::string folder_path = "settings/";
        std::string file_path = folder_path + "settings.json";
    #elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
        __NetBSD__
        char user[64];
        getlogin_r(user, 64);

        std::string folder_path = "/home/" + std::string(user) + "/.config/termi/";
        std::string file_path = folder_path + "settings.json";  
    #else
        std::string file_path = " ";
    #endif
    
    std::string default_json = "{\"startup_command\": \"none\",\"width\" : 650,\"height\" : 650,\"font_name\" : \"default\",\"font_size\" : 16,\"glyph-range\" : \"default\",\"gui-model\" : 0}";

    auto mode = std::ios::app | std::ios::in;
    std::string temp_str = "";

    if (!std::filesystem::exists(folder_path) && !std::filesystem::is_directory(folder_path))
    {
        std::filesystem::create_directory(folder_path);
    }

    if (!CheckFile(file_path.c_str()))
    {
        std::fstream file(file_path, mode);
        file << default_json;
        file.close();
    }

    FILE *file = fopen(file_path.c_str(), "r");
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
        case 6: /* gui model */
            return 0;
            break;

        default:
            std::get<1>(vpprender[vpprender_id])->AddLog("Invalid id %d!\n", id);
            std::get<1>(vpprender[vpprender_id])->AddLog(
                "ID list: \n%s%s%s%s%s%s%s%s%s%s%s",
                "0 - read startup command\n"
                "1 - read width\n",
                "2 - read height\n",
                "3 - set variable font_name to the font name\n",
                "4 - read font size\n",
                "6 - read gui model type\n");
            return 1;
            break;
        }

        return 1;
    }

    char buffer[1024];

    fread(buffer, 1024, 1, file);
    fclose(file);

    struct json_object *parsed_json;
    struct json_object *j_startup_command;
    struct json_object *j_width;
    struct json_object *j_height;
    struct json_object *j_font_name;
    struct json_object *j_font_size;
    struct json_object* j_gui_model;

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "startup_command", &j_startup_command);
    json_object_object_get_ex(parsed_json, "width", &j_width);
    json_object_object_get_ex(parsed_json, "height", &j_height);
    json_object_object_get_ex(parsed_json, "font_name", &j_font_name);
    json_object_object_get_ex(parsed_json, "font_size", &j_font_size);
    json_object_object_get_ex(parsed_json, "gui-model", &j_gui_model);

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

    case 6: /* gui model */
        return json_object_get_int(j_gui_model);
        break;

    default:
        std::get<1>(vpprender[vpprender_id])->AddLog("Invalid id %d!\n", id);
        std::get<1>(vpprender[vpprender_id])->AddLog(
            "ID list: \n%s%s%s%s%s%s%s%s%s%s%s",
            "0 - read startup command\n"
            "1 - read width\n",
            "2 - read height\n",
            "3 - set variable font_name to the font name\n",
            "4 - read font size\n",
            "6 - read gui model type\n");
        return 1;
        break;
    }

    return 0;
}

void Renderer::SetFont(ImGuiIO &io)
{
    #if defined _WIN32 || defined _WIN64
        std::string folder_path = "settings/";
        std::string file_path = folder_path + "settings.json";
    #elif __APPLE__ || __MACH__ || __linux__ || __FreeBSD__ || __OpenBSD__ || \
        __NetBSD__
        char user[64];
        getlogin_r(user, 64);

        std::string folder_path = "/home/" + std::string(user) + "/.config/termi/";
        std::string file_path = folder_path + "settings.json";  
    #else
        std::string file_path = " ";
    #endif

    FILE *file = fopen(file_path.c_str(), "r");
    char buffer[1024];

    fread(buffer, 1024, 1, file);
    fclose(file);

    struct json_object *parsed_json;
    struct json_object *j_glyph_range;

    parsed_json = json_tokener_parse(buffer);
    json_object_object_get_ex(parsed_json, "glyph-range", &j_glyph_range);

    std::string glyph_range_str = json_object_get_string(j_glyph_range);

    Settings(3);
    if (font_name != "default")
    {
        if (CheckFile(font_name.c_str()) == false)
        {
            printf("Cannot find font, loading default font...!\n");
            return;
        }
    }

    if (glyph_range_str == "korean")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesKorean());
    }

    else if (glyph_range_str == "chinese_full")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesChineseFull());
    }

    else if (glyph_range_str == "chinese_simplified_common")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesChineseSimplifiedCommon());
    }

    else if (glyph_range_str == "japanese")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesJapanese());
    }

    else if (glyph_range_str == "cyrillic")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesCyrillic());
    }

    else if (glyph_range_str == "thai")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesThai());
    }

    else if (glyph_range_str == "vietnamese")
    {
        io.Fonts->AddFontFromFileTTF(font_name.c_str(), Settings(4), NULL, io.Fonts->GetGlyphRangesVietnamese());
    }

    else if (glyph_range_str == "latin-ex-a")
    {
        /* Source of code: https://github.com/kmar/Sweet16Font/blob/master/Sweet16_ImGui.inl */
        static const ImWchar Sweet16_ranges[] =
            {
                0x0020,
                0x017F, // Basic Latin + Latin supplement + Latin extended A
                0,
            };

        ImFontConfig config;
        config.OversampleH = 1;
        config.OversampleV = 1;
        config.PixelSnapH = true;
        config.SizePixels = 16;
        // the proportional variant probably looks better with 1px extra horizontal spacing (just uncomment the following line)
        // config.GlyphExtraSpacing.x = 1;

        // copy font name manually to avoid warnings
        const char *name = "font/Sweet16.ttf, 16px";
        char *dst = config.Name;

        while (*name)
            *dst++ = *name++;
        *dst = '\0';

        io.Fonts->AddFontFromMemoryCompressedBase85TTF(Sweet16_compressed_data_base85, config.SizePixels, &config, Sweet16_ranges);
    }

    else
    {
        /* ignore */
    }
}

/* Check if file exists */
bool Renderer::CheckFile(const char *name)
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

/**
 * Entry point for server
*/
void CreateServer()
{
    int server_sockfd = 0;
    int client_sockfd = 0;

    ClientList* now;

    /* Create socket */
    server_sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (server_sockfd == -1) 
    {
        printf("Failed to create a socket!\n");
        return;
    }

    /* Socket information */
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = INADDR_ANY;
    server_info.sin_port = htons(5555);

    /* Bind and listen */
    bind(server_sockfd, (struct sockaddr *)&server_info, s_addrlen);
    listen(server_sockfd, 5);

    /* Print server IP */
    getsockname(server_sockfd, (struct sockaddr*) &server_info, (socklen_t*) &s_addrlen);
    printf("Game started on: %s:%d!\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    /* Initial linked list for clients */
    root = newNode(server_sockfd, inet_ntoa(server_info.sin_addr));
    now = root;

    while (1) 
    {
        client_sockfd = accept(server_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);

        /* Print client IP */
        getpeername(client_sockfd, (struct sockaddr*) &client_info, (socklen_t*) &c_addrlen);
        printf("Client %s:%d joined the game!\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

        /* Append linked list for clients */
        ClientList *c = newNode(client_sockfd, inet_ntoa(client_info.sin_addr));
        c->prev = now;
        now->link = c;
        now = c;

        ClientArg arguments;

        arguments.now = now;
        arguments.p_client = c;

        pthread_t id;
        if (pthread_create(&id, NULL, client_handler, (void *)&arguments) != 0) 
        {
            perror("Create pthread error!\n");
            return;
        }
    }

    return;
}

/**
 * Draw tabs
 * @param style 
*/
void DrawTab(ImGuiStyle& style)
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
            if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
                active_tabs.push_back(next_tab_id++); // Add new tab

        // Submit our regular tabs
        for (int n = 0; n < active_tabs.Size;)
        {
            bool open = true;
            char name[16] = "Termi";
            snprintf(name, IM_ARRAYSIZE(name), "%04d", n);
            if (ImGui::BeginTabItem(name, &open, ImGuiTabItemFlags_None) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                vpprender_id = n;
                std::get<0>(vpprender[vpprender_id])->DrawMenu(style);
                std::get<1>(vpprender[vpprender_id])->Draw();
                ImGui::EndTabItem();
            }

            if (!open)
                active_tabs.erase(active_tabs.Data + n);
            else
                n++;
        }

        ImGui::EndTabBar();
    }
}

/**
 * Entry point for ImGui part of Termi
 * @param style
*/
void main_code(ImGuiStyle& style)
{
    /* ImGui window creation */
    ImGui::Begin("Termi",
                 NULL,
                 ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse |
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_MenuBar |
                     ImGuiInputTextFlags_AllowTabInput);

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

    /* Staring values */
    vpprender.push_back({
        std::make_unique<Renderer>(),
        std::make_unique<Console>(),
        std::make_unique<Vars>()
    });

    /* Draw tabs and menu bar */
    DrawTab(style);

    /* Language dialog */
    if (std::get<2>(vpprender[vpprender_id])->language_dialog)
    {
        std::get<0>(vpprender[vpprender_id])->ChooseLanguageDialog(NULL);
    }

    /* About Termi dialog */
    if (std::get<2>(vpprender[vpprender_id])->termi_dialog)
    {
        std::get<0>(vpprender[vpprender_id])->TermiDialog(NULL);
    }

    /* About ImGui dialog */
    if (std::get<2>(vpprender[vpprender_id])->imgui_dialog)
    {
        std::get<0>(vpprender[vpprender_id])->ImGuiDialog(NULL);
    }

    /* Get window width and height */
    window_width = ImGui::GetWindowWidth();
    window_height = ImGui::GetWindowHeight();

    /* End of window */
    ImGui::End();
}

/**
 * AddLog but outside of struct so it is visible from .so/.dll files
 * @param fmt - string
 */
void AddLog(const char *fmt, ...)
{
    std::get<1>(vpprender[vpprender_id])->AddLog(fmt);

    if (!vpprender.empty())
    {
        if (std::get<2>(vpprender[vpprender_id])->server)
        {
            send_to_all_clients(fmt);
        }
    }
}
