/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Settings class implementation file
*/

#include "settings.hpp"

Settings::Settings()
{
    CreateFile();
}

Settings::~Settings()
{

}

std::string Settings::GetStartupCommand()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "startup_command") == 0)
        {
            return std::string(json_object_get_string(val));
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return "";
}

int Settings::GetWidth()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "width") == 0)
        {
            return json_object_get_int(val);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

int Settings::GetHeight()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "height") == 0)
        {
            return json_object_get_int(val);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

std::string Settings::GetFontName()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "font_name") == 0)
        {
            return std::string(json_object_get_string(val));
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return "";
}

int Settings::GetFontSize()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "font_size") == 0)
        {
            return json_object_get_int(val);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

std::string Settings::GetGlyphRange()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "glyph-range") == 0)
        {
            return std::string(json_object_get_string(val));
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return "";
}

int Settings::GetGuiModel()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "gui-model") == 0)
        {
            return json_object_get_int(val);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

int Settings::GetPort()
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path.c_str());
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "port") == 0)
        {
            return json_object_get_int(val);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

void Settings::CreateFile()
{
#if defined __APPLE__ || defined __MACH__ || defined __linux__ || \
        defined __FreeBSD__ || defined __OpenBSD__ || defined __NetBSD__
    char user[64];
    getlogin_r(user, 64);

    std::string folder_path = "/home/" + std::string(user) + "/.config/termi/"
#else
    std::string folder_path = "settings/";
#endif

    std::string file_path = folder_path + "settings.json";
    std::string default_json = "{\"startup_command\":\"none\",\"width\":650,\"height\":650,\"font_name\":\"default\",\"font_size\":16,\"glyph-range\":\"default\",\"gui-model\":0,\"port\":5555}";

    auto mode = std::ios::app | std::ios::in;
    std::string temp_str = "";

    if (!std::filesystem::exists(folder_path) || !std::filesystem::is_directory(folder_path))
    {
        std::filesystem::create_directory(folder_path);
    }

    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path))
    {
        std::fstream file(file_path, mode);
        file << default_json;
        file.close();
    }

    path = file_path;
}
