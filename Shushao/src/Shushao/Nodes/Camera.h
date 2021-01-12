#pragma once

#include "Shushao/Renderer/Color.h"
#include "Shushao/Core/Entity.h"

namespace Shushao {

    class Camera : public Entity
    {
    public:

        Camera();

        inline virtual void Init() { UpdateProjectionMatrix(); UpdateViewMatrix();}

        virtual void UpdateProjectionMatrix() {};
        virtual void UpdateViewMatrix();

        inline const glm::mat4& GetViewMatrix() const { return viewMatrix; }
        inline const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
        inline const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }
        inline const Color& GetBackgroundColor() const { return backgroundColor; }
        inline float GetAspect() const { return aspect; }
        inline float GetDepth() const { return depth; }
        inline float GetFarClipPlane() const { return farClipPlane; }
        inline float GetNearClipPlane() const { return nearClipPlane; }
        inline const glm::vec2& GetViewportSize() { return viewportSize; }
        //inline Rect GetRect() const { return rect; }

        void SetDepth(float _depth) { depth = _depth; }
        void SetFarClipPlane(float _farClipPlane) { farClipPlane = _farClipPlane; UpdateProjectionMatrix(); UpdateViewMatrix();  InvalidateMatrix(); }
        void SetNearClipPlane(float _nearClipPlane) { nearClipPlane = _nearClipPlane; UpdateProjectionMatrix(); UpdateViewMatrix(); InvalidateMatrix(); }
        void SetBackgroundColor(const Color& _color) { backgroundColor = _color; }
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

        inline void InvalidateMatrix() { matrixInvalid = true; }

        void Update();

    protected:
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;

        bool matrixInvalid = true;

        Color backgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };
        float aspect = 16.0f / 9.0f;
        float depth = 3.0f;
        float farClipPlane = 10.0f;
        float nearClipPlane = -3.0f;
        glm::vec2 viewportSize = { 0.0f, 0.0f };

        //Rect& rect;
    };

}  // namespace Shushao
