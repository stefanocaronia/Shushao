#pragma once

#include "Color.h"
#include "Entity.h"

namespace Shushao {

    class Camera : public Entity
    {
    public:
        inline virtual void Init() { UpdateProjectionMatrix(); }
        virtual void UpdateProjectionMatrix() = 0;
        virtual void UpdateViewMatrix();

        inline void Invalidate() { valid = false; }

        inline glm::mat4 GetViewMatrix() const { return viewMatrix; }
        inline glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
        inline Color GetBackgroundColor() const { return backgroundColor; }
        inline float GetAspect() const { return aspect; }
        inline float GetDepth() const { return depth; }
        inline float GetFarClipPlane() const { return farClipPlane; }
        inline float GetNearClipPlane() const { return nearClipPlane; }
        inline glm::vec2 GetViewportSize() { return viewportSize; }
        //inline Rect GetRect() const { return rect; }

        void setDepth(float _depth) { depth = _depth; }
        void setFarClipPlane(float _farClipPlane) { farClipPlane = _farClipPlane; UpdateProjectionMatrix(); Invalidate(); }
        void setNearClipPlane(float _nearClipPlane) { nearClipPlane = _nearClipPlane; UpdateProjectionMatrix();  Invalidate(); }
        void setBackgroundColor(const Color& _color) { backgroundColor = _color; }
        //inline void SetRect(const Rect& _rect) const { rect = _rect; }

        inline void Print()
        {
            std::cout << "  - " << "backgroundColor: " << backgroundColor.r << " " << backgroundColor.g << " " << backgroundColor.b << " " << backgroundColor.a << std::endl;
            std::cout << "  - " << "aspect: " << aspect << std::endl;
            std::cout << "  - " << "depth: " << depth << std::endl;
            std::cout << "  - " << "farClipPlane: " << farClipPlane << std::endl;
            std::cout << "  - " << "nearClipPlane: " << nearClipPlane << std::endl;
            //std::cout << "  - " << "rect: " << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << std::endl;
        }

    protected:
        Color backgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        float aspect;
        bool valid = false;

        float depth = 3.0f;
        float farClipPlane = 1000.0f;
        float nearClipPlane = 3.0f;

        glm::vec2 viewportSize = { 0.0f, 0.0f };
        //Rect& rect;
    };

}  // namespace se
