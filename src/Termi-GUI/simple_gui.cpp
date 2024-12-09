/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Main file for simple console model
 */

#include "simple_gui.hpp"

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

/* ------------------------------------------------------------------------- */

SimpleConsole::SimpleConsole()
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

SimpleConsole::~SimpleConsole()
{
    FullClearLog();
    for (int i = 0; i < History.Size; i++)
        free(History[i]);
}

template <typename T>
int SimpleConsole::LoadDynamicLibrary(const char* path, const char* function, T argument)
{
    #if defined _WIN32 || defined _WIN64
        typedef int(__cdecl* FUNC)(T);

        HINSTANCE hinstLib;
        FUNC ProcAdd;
        BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;

        // Get a handle to the DLL module
        hinstLib = LoadLibrary(LPCSTR(path));
        
        // If the handle is valid, try to get the function address.
        if (hinstLib != NULL)
        {
            ProcAdd = (FUNC)GetProcAddress(hinstLib, function);

            // If the function address is valid, call the function.
            if (NULL != ProcAdd)
            {
                fRunTimeLinkSuccess = TRUE;
                (ProcAdd)(argument);
            }

            else
            {
                printf("Error loading function '%s' from '%s'!\n", function, path);
                return 1;
            }

            // Free the DLL module.
            fFreeResult = FreeLibrary(hinstLib);
        }

        // If unable to call the DLL function, use an alternative.
        if (!fRunTimeLinkSuccess)
        {
            printf("Error loading function '%s' from '%s'!\n", function, path);
            return 1;
        }

        return 0;

    #elif defined __APPLE__ || defined __MACH__ || defined __linux__ || \
        defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
        void *handle;
        void (*func)(T);
        char *error;

        handle = dlopen(path, RTLD_LAZY);
        if (!handle) 
        {
            fputs (dlerror(), stderr);
            puts(" ");

            return 1;
        }

        func = reinterpret_cast<void (*)(T)>(dlsym(handle, function));
        if ((error = dlerror()) != NULL)
        {
            fputs(error, stderr);
            return 1;
        }

        (*func)(argument);
        dlclose(handle);

        return 0;
    #endif

    return 1;
}

void SimpleConsole::ClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();

    TypeTermi();
}

void SimpleConsole::FullClearLog()
{
    for (int i = 0; i < Items.Size; i++)
        free(Items[i]);
    Items.clear();
}

void SimpleConsole::AddLog(const char *fmt, ...)
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

void SimpleConsole::Draw()
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

    /* Retrieve client's command */
    bool execute_command = false;
    if (server)
    {
        std::unique_lock<std::mutex> lock(client_input_mutex);

        if (client_input == "")
        {
            goto skip;
        }

        std::cout << "Output: " + client_input;
        strncpy(InputBuf, client_input.c_str(), 256);
        execute_command = true;
        client_input = "";

skip:
        lock.unlock();
    }

    bool reclaim_focus = false;
    if (!ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0) && !alReadyFocusOnInputBar) /* can i ask myself? */
    {
        ImGui::SetKeyboardFocusHere(0);
        alReadyFocusOnInputBar = true; /* can i ask myself? */
    }

    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (execute_command || ImGui::InputText(cwd, InputBuf, IM_ARRAYSIZE(InputBuf), input_text_flags, &TextEditCallbackStub, (void*)this))
    {
        s = InputBuf;
        Strtrim(s);

        if (s[0])
        {
            ExecCommand(s);
        }

        strcpy(s, "");
        reclaim_focus = true;

        execute_command = false;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
}

void SimpleConsole::ExecCommand(std::string command_line, ...)
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
        LoadDynamicLibrary(COMMANDS_PATH, result->second.c_str(), arguments);
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
        AddLog("LICENSE > MIT");
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

        LoadDynamicLibrary(arguments[1].c_str(), arguments[2].c_str(), argument.c_str());
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

void SimpleConsole::TypeTermi()
{
    AddLog("\nTermi> ");
}

int SimpleConsole::TextEditCallback(ImGuiInputTextCallbackData *data)
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
