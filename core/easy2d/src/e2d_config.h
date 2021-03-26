#ifndef CONFIG_H
#define CONFIG_H

#include <ctime>
#include <iostream>
#include <algorithm>
#include <tchar.h>
#include <stdio.h>

#include "logger.h"
#include "base/e2d_types.h"
#include "base/e2d_singleton.h"

#define LOG_WARN logger_ctx<log_level::LOG_LEVEL_WARN>(__FILE__, __LINE__)
#define LOG_INGO logger_ctx<log_level::LOG_LEVEL_INFO>(__FILE__, __LINE__)
#define LOG_DEBUG logger_ctx<log_level::LOG_LEVEL_DEBUG>(__FILE__, __LINE__)
#define LOG_ERROR logger_ctx<log_level::LOG_LEVEL_ERROR>(__FILE__, __LINE__)
#define LOG_FATAL logger_ctx<log_level::LOG_LEVEL_FATAL>(__FILE__, __LINE__)

#if defined(_WIN32)
    #ifndef NOMINMAX 
        #define NOMINMAX 
    #endif
    #define PLATFORM_WINDOW
    #define _CRT_SECURE_NO_DEPRECATE
    #define _CRT_NONSTDC_NO_WARNINGS
    #include <windows.h>
    #include <gl/glew.h>
    #include <gl/GL.h>
    #include <gl/glu.h>
#endif

#endif