/**
 * @author Andrej Bartulin
 * PROJECT: Termi - powerful terminal with OpenGL & Dear ImGui rendering system
 * LICENSE: MIT
 * DESCRIPTION: Translation file
 */

#pragma once

#include <map>
#include <string>
#include <vector>

namespace Translation
{
    /**
    * Order of languages in `text` map.
    * Put English at the front and sort rest alphabetically.
    */
    static std::vector<std::string> language_id = {"English", "Croatian", "Esperanto", "German", "Spanish", "Vietnamese"};
    
    /**
    * Map conststing of the original English text and its translations.
    * Use `language_id` vector to determine position of language in vector.
    * 
    * @param first English text
    * @param second vector containing translated texts, check `language_id` vector to determine position of language
    */
    static std::map<std::string, std::vector<std::string>> text =
    {
        {"Terminal", {"Terminal", "Terminalo", "Terminal", "Terminal", "Dòng lệnh"}},
        {"Server", {"Server", "Servilo", "Server", "Servidor", "Máy chủ"}},
        {"Exit", {"Izađi", "Eliri", "Beenden", "Salir", "Thoát"}},

        {"Edit", {"Uredi", "Redakti", "Bearbeiten", "Editar", "Chỉnh sửa"}},
        {"Change theme (light/dark)", {"Promijeni temu (svijetla/tamna)", "Ŝanĝi temon (luma/malhelma)", "Thema wechseln (hell/dunkel)", "Cambiar tema (claro/oscuro)", "Đổi chủ đề nền (sáng/tối)"}},
        {"Change theme", {"Promijeni temu", "Ŝanĝi temon", "Thema wechseln", "Cambiar tema", "Đổi chủ đề nền"}},
        {"Change language", {"Promijeni jezik", "Ŝanĝi lingvon", "Sprache ändern", "Cambiar idioma", "Đổi ngôn ngữ"}},

        {"About", {"O Termiju", "Pri", "Über", "Acerca de", "Giới thiệu"}},
        {"About Termi", {"O Termiju", "Pri Termi", "Über Termi", "Acerca de Termi", "Về Termi"}},
        {"About Dear ImGui", {"O Dear ImGui-u", "Pri Dear ImGui", "Über Dear ImGui", "Acerca de Dear ImGui", "Về Dear ImGui"}},

        {"Input", {"Unos", "Enigo", "Eingabe", "Entrada", "Nhập vào"}},
        {"New Tab", {"Nova kartica", "Nova langeto", "Neuer Tab", "Nueva pestaña", "Thẻ mới"}},
        {"New profile", {"Novi profil", "Nova profilo", "Neues Profil", "Nuevo perfil", "Hồ sơ mới"}},
        {"Remote connection", {"Mrežno povezivanje", "Fora konekto", "Fernverbindung", "Conexión remota", "Kết nối"}},
        {"Client", {"Klijent", "Kliento", "Client", "Cliente", "Máy khách"}},
    };
};
