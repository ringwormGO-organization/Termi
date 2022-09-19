#pragma once

#if API_EXPORT
#define _API __declspec(dllexport)
#else
#define _API __declspec(dllimport)
#endif

extern "C" _API void command_test_10();
