#ifndef CONFIG_H
#define CONFIG_H

#include <ctime>
#include <iostream>
#include <algorithm>
#include <tchar.h>
#include <stdio.h>

#include "logger.h"
#include "base/e2d_types.h"
#include "base/e2d_utils.h"
#include "base/e2d_singleton.h"

#if defined(_WIN32)
    #ifndef NOMINMAX 
        #define NOMINMAX 
    #endif
    #define PLATFORM_WINDOW
    #define GLFW_INCLUDE_NONE
    #define _CRT_SECURE_NO_DEPRECATE
    #define _CRT_NONSTDC_NO_WARNINGS
    #include <windows.h>
    #include <glad/glad.h>
    #include <glfw/glfw3.h>
#endif

#endif