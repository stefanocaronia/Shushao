#pragma once

#define _USE_MATH_DEFINES
#define CONSOLE_COLORS_ENABLED

#ifdef SE_PLATFORM_WINDOWS
    #undef ERROR
    #undef SendMessage
#endif

#ifdef SE_DEBUG
    #define SE_ENABLE_ASSERTS
#endif

#ifdef SE_ENABLE_ASSERTS
    #define SE_ASSERT(x, ...)                                      \
            {                                                          \
                if (!(x)) {                                            \
                    DEBUG_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
                    __debugbreak();                                    \
                }                                                      \
            }
    #define SE_CORE_ASSERT(x, ...)                                      \
            {                                                               \
                if (!(x)) {                                                 \
                    DEBUG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
                    __debugbreak();                                         \
                }                                                           \
            }
#else
    #define SE_ASSERT(x, ...)
    #define SE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f

#define LIB_SHUSHAO "shushaores.dll"

#define SE_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

// Helper classes
#include "Helper/BitsafeEnum.h"