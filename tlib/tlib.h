/**
 * @author Andrej Bartulin
 * @author Stjepan Bilić Matišić
 * PROJECT: tlib - Termi library for connecting executables and Termi OpenGL version
 * LICENSE: BSD-3-Clause-License
 * DESCRIPTION: tlib main header file
*/

#pragma once

#define ENABLE
#define INCLUDE_C
#define INCLUDE_CPP
#define USE_STD

#ifdef INCLUDE_C
    #ifndef INCLUDE_CPP
        #ifdef _WIN32
            #pragma message ("C is sometimes unsupported!")
        #elif _WIN64
            #pragma message ("C is sometimes unsupported!")
        #elif __APPLE__ || __MAC__
            #warning "C is sometimes unsupported!"
        #elif __linux__
            #warning "C is sometimes unsupported!"
        #elif __FreeBSD__
            #warning "C is sometimes unsupported!"
        #elif __unix || __unix__
            #warning "C is sometimes unsupported!"
        #else
            #warning "C is sometimes unsupported!"
        #endif
    #endif
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <signal.h>
#endif

#ifdef INCLUDE_CPP
    #include <iostream>
    #include <string>
    #include <fstream>
    #include <map>
    #include <filesystem>
    #include <signal.h>

    #ifdef USE_STD
        using namespace std;
    #endif
#endif

#ifdef ENABLE
    #define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#endif