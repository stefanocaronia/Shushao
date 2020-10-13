#pragma once

#include "sepch.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#define _USE_MATH_DEFINES
#define CONSOLE_COLORS_ENABLED

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

const std::string LIB_SHUSHAO = "shushaores.dll";

namespace se {

// typeid without rtti
using TypeInfo = void*;
template <typename T>
TypeInfo _typeid() {
    return reinterpret_cast<TypeInfo>(&_typeid<T>);
}
#define TYPEID(T) _typeid<T>()

enum class Align {
    CENTER,
    LEFT,
    RIGHT,
    TOPLEFT,
    TOPRIGHT,
    TOP,
    BOTTOM,
    BOTTOMLEFT,
    BOTTOMRIGHT,
    CUSTOM
};

enum class RenderMode {
    WORLD,
    SCREEN,
    CAMERA
};

namespace PivotPosition {
    const glm::vec2 CENTER = {0.5f, 0.5f};
    const glm::vec2 LEFT = {0.0f, 0.5f};
    const glm::vec2 RIGHT = {1.0f, 0.5f};
    const glm::vec2 TOPLEFT = {0.0f, 1.0f};
    const glm::vec2 TOPRIGHT = {1.0f, 1.0f};
    const glm::vec2 TOP = {0.5f, 1.0f};
    const glm::vec2 BOTTOM = {0.5f, 0.0f};
    const glm::vec2 BOTTOMLEFT = {0.0f, 0.0f};
    const glm::vec2 BOTTOMRIGHT = {1.0f, 0.0f};
}  // namespace PivotPosition

struct AnchorPoints {
    glm::vec2 min;
    glm::vec2 max;
};

namespace AnchorPreset {  //     		       MIN		     MAX
    const AnchorPoints TOPLEFT = {{0.0f, 1.0f}, {0.0f, 1.0f}};
    const AnchorPoints TOP = {{0.5f, 1.0f}, {0.5f, 1.0f}};
    const AnchorPoints TOPRIGHT = {{1.0f, 1.0f}, {1.0f, 1.0f}};
    const AnchorPoints TOPSTRETCH = {{0.0f, 1.0f}, {1.0f, 1.0f}};

    const AnchorPoints LEFT = {{0.0f, 0.5f}, {0.0f, 0.5f}};
    const AnchorPoints CENTER = {{0.5f, 0.5f}, {0.5f, 0.5f}};
    const AnchorPoints RIGHT = {{1.0f, 0.5f}, {1.0f, 0.5f}};
    const AnchorPoints MIDDLESTRETCH = {{0.0f, 0.5f}, {1.0f, 0.5f}};

    const AnchorPoints BOTTOMLEFT = {{0.0f, 0.0f}, {0.0f, 0.0f}};
    const AnchorPoints BOTTOM = {{0.5f, 0.0f}, {0.5f, 0.0f}};
    const AnchorPoints BOTTOMRIGHT = {{1.0f, 0.0f}, {1.0f, 0.0f}};
    const AnchorPoints BOTTOMSTRETCH = {{0.0f, 0.0f}, {1.0f, 0.0f}};

    const AnchorPoints STRETCH = {{0.0f, 0.0f}, {1.0f, 1.0f}};
}  // namespace AnchorPreset

}  // namespace se
