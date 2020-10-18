#include "Core.h"

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
