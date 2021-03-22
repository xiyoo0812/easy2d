#ifndef CONFIG_H
#define CONFIG_H

#include <ctime>
#include <iostream>
#include <algorithm>

#include "base/e2d_types.h"

#if defined(_WIN32)
    #ifndef NOMINMAX 
        #define NOMINMAX 
    #endif
    #define PLATFORM_WINDOW
    #include <windows.h>
    #include <gl/GL.h>
    #include <GL/glu.h>
#endif

#endif