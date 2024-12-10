/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Main file for GUI code
 */

#include "imgui_code.hpp"

#include "simple_console.hpp"
#include "advanced_console.hpp"

#if defined _WIN32 || defined _WIN64
    #pragma warning(disable : 4996)    
#endif

/** 
 * Vector holding unique pointer(s) of ConsoleBase class
 */
std::vector<std::unique_ptr<ConsoleBase>> vrenderer;

/**
 * Current vrenderer element in use
 */
size_t vrenderer_id;

/* ------------------------------------------------------------------------- */

void GUI::DrawMenu(ImGuiStyle& style)
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu(ChooseLanguage("Terminal").c_str()))
        {
            if (ImGui::MenuItem(ChooseLanguage("Server").c_str()) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (!server) /* server is off */
                {
                    server = true;

                    std::thread server(CreateServer);
                    server.detach();
                }

                else /* server is on */
                {
                    server = false;
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem(ChooseLanguage("Exit").c_str()) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                exit(0);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ChooseLanguage("Edit").c_str()))
        {
            if (ImGui::MenuItem(ChooseLanguage("Change theme (light/dark)").c_str()) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (isDarkTheme)
                {
                    ImGui::StyleColorsLight();
                    isDarkTheme = false;
                }

                else
                {
                    ImGui::StyleColorsDark();
                    isDarkTheme = true;
                }
            }

            if (ImGui::MenuItem(ChooseLanguage("Change theme").c_str()))
            {
                std::random_device dev;
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> dist(0, themes.size() - 1);

                theme = themes.at(static_cast<int>(dist(rng)));

                if (theme == "dark_red")
                {
                    style.Colors[ImGuiCol_WindowBg] = ImColor(84, 3, 34);
                }

                else if (theme == "aqua")
                {
                    style.Colors[ImGuiCol_WindowBg] = ImColor(0, 255, 255);
                }

                else if (theme == "some_yellow")
                {
                    style.Colors[ImGuiCol_WindowBg] = ImColor(204, 163, 80);
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem(ChooseLanguage("Change language").c_str()) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (!language_dialog)
                {
                    language_dialog = true;
                    ChooseLanguageDialog(NULL);
                }
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu(ChooseLanguage("About").c_str()))
        {
            if (ImGui::MenuItem(ChooseLanguage("About Termi").c_str()) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
            {
                if (termi_dialog == false)
                    termi_dialog = true;
                else
                    termi_dialog = false;
            }

            if (ImGui::MenuItem(ChooseLanguage("About Dear ImGui").c_str()) || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
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

std::string GUI::ChooseLanguage(std::string text)
{
    if (language == "English")
    {
        return text;
    }

    size_t language_id = 0;
    auto it = std::find(Translation::language_id.begin(), Translation::language_id.end(), language);

    if (it != Translation::language_id.begin())
    {
        language_id = it - Translation::language_id.begin();
    }

    else
    {
        std::cout << "Language '" << language << "' has not been found in `language_id`!\n";
        return text;
    }

    for (auto it = Translation::text.begin(); it != Translation::text.end(); ++it)
    {
        if (it->first == text)
        {
            /* -1 because English is not in map's vector */
            return it->second.at(language_id - 1).c_str();
        }
    }

    return text;
}

void GUI::ChooseLanguageDialog(bool *p_open)
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
            language_dialog = false;
        }

        ImGui::EndPopup();
    }

    ImGui::Text("Choose language / Odaberi jezik");
    ImGui::Text(" "); /* empty space */

    if (ImGui::Button("English (default)") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language = "English";
    }

    if (ImGui::Button("Croatian / Hrvatski") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language = "Croatian";
    }

    if (ImGui::Button("Esperanto / Esperanto") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language = "Esperanto";
    }

    if (ImGui::Button("German / Deutsch") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language = "German";
    }

    if (ImGui::Button("Spanish / Español") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language = "Spanish";
    }

    if (ImGui::Button("Vietnamese / Tiếng Việt") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language = "Vietnamese";
    }

    if (ImGui::Button("X") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        language_dialog = false;
    }

    ImGui::End();
}

void GUI::TermiDialog(bool *p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(500, 700));
    if (!ImGui::Begin(ChooseLanguage("About Termi").c_str(), p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window"))
        {
            termi_dialog = false;
        }

        ImGui::EndPopup();
    }

    if (ImGui::Button("X") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        termi_dialog = false;
    }

    ImGui::Text("AUTHORS > Andrej Bartulin and Stjepan Bilic Matisic");
    ImGui::Text("ABOUT > A powerful terminal made in C++ which use OpenGL and ImGui.\nIf you have issue check our GitHub repo and report issue.");
    ImGui::Text("If you know how to fix fell free to contribute it through pull requests on GitHub.");
    ImGui::Text("LICENSE > MIT");
    ImGui::Text("REPO > https://github.com/ringwormGO-organization/Termi");

    ImGui::End();
}

void GUI::ImGuiDialog(bool *p_open)
{
    ImGui::SetWindowPos(ImVec2(200, 200));
    ImGui::SetWindowSize(ImVec2(500, 300));
    if (!ImGui::Begin(ChooseLanguage("About Dear ImGui").c_str(), p_open))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Button("Close window"))
        {
            imgui_dialog = false;
        }

        ImGui::EndPopup();
    }

    if (ImGui::Button("X") || (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)))
    {
        imgui_dialog = false;
    }

    ImGui::Text("ABOUT > Dear ImGui: Bloat-free Graphical User interface\nfor C++ with minimal dependencies.");
    ImGui::Text("REPO > https://github.com/ocornut/imgui");

    ImGui::End();
}

/* ------------------------------------------------------------------------- */

ConsoleBase::ConsoleBase()
{

}

ConsoleBase::~ConsoleBase()
{

}

void ConsoleBase::AddLog(const char *fmt, ...)
{

}

void ConsoleBase::Draw()
{

}

/* ------------------------------------------------------------------------- */

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
                vrenderer_id = n;
                vrenderer[vrenderer_id]->DrawMenu(style);
                vrenderer[vrenderer_id]->Draw();
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

    if (!alReadyPrinted)
    {
        std::cout << "Dear ImGui has been initialized.\n";
        alReadyPrinted = true;
    }

    ImGui::SetCursorPosX(window_width + window_width / 200 - 200);
    ImGui::TextColored(ImVec4(0, 0.88f, 0.73f, 1.00f), "(%.3f ms/frame, %.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    Settings settings;
    int console_model = settings.GetConsoleModel();

    /* simple console model || unsupported console model, not simple nor advanced one */
    if (console_model == 0 || (console_model != 0 && console_model != 1))
    {
        /* Staring values */
        vrenderer.push_back({
            std::make_unique<SimpleConsole>(),
        });
    }

    else if (console_model == 1)
    {
        vrenderer.push_back({
            std::make_unique<AdvancedConsole>(),
        });
    }

    /* Draw tabs and menu bar */
    DrawTab(style);

    /* Language dialog */
    if (vrenderer[vrenderer_id]->language_dialog)
    {
        vrenderer[vrenderer_id]->ChooseLanguageDialog(NULL);
    }

    /* About Termi dialog */
    if (vrenderer[vrenderer_id]->termi_dialog)
    {
        vrenderer[vrenderer_id]->TermiDialog(NULL);
    }

    /* About ImGui dialog */
    if (vrenderer[vrenderer_id]->imgui_dialog)
    {
        vrenderer[vrenderer_id]->ImGuiDialog(NULL);
    }

    /* Get window width and height */
    window_width = ImGui::GetWindowWidth();
    window_height = ImGui::GetWindowHeight();

    /* End of window */
    ImGui::End();
}

void AddLog(const char *fmt, ...)
{
    vrenderer[vrenderer_id]->AddLog(fmt);

    if (vrenderer[vrenderer_id]->server)
    {
        send_to_all_clients(fmt);
    }
}
