/**
 * @author Andrej Bartulin
 * PROJECT: Termi-Linux version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Header file for console
 * INFORAMTION: Install OpenGL and run this command in terminal: clear && cmake . && make && ./Termi-OpenGL
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    extern void*    CmbalIO_new();
    extern void     CmbalIO_delete(void* con);
    extern void     CmbalIO_AddLog(void* con, const char* fmt, ...);
#ifdef __cplusplus
}
#endif