/**
 * @author Andrej Bartulin
 * PROJECT: Termi version with OpenGL and Dear ImGui rendering system
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: Settings file
 * INFORMATION: #undef - disable feature | #define - enable feature
*/

#pragma once

#ifdef _WIN32
	#define USE_PREINSTALLED_HEADERS
#elif _WIN64
	#define USE_PREINSTALLED_HEADERS
#else
	#undef USE_PREINSTALLED_HEADERS
#endif

#define PRINT_WHEN_WINDOW_IS_CREATED
#undef PRINT_FPS_CONSOLE
#define PRINT_FPS
