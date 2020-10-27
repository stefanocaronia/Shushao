#pragma once

#include "Color.h"
#include "SpatialNode.h"

namespace Shushao {

    class Camera : public SpatialNode
    {
    public:
        void Init();

        inline glm::mat4 GetViewMatrix() const { return viewMatrix; }
        inline glm::mat4 GetProjectionMatrix() const { return projectionMatrix; }
        inline Color& GetBackgroundColor() const { return backgroundColor; }
        inline float GetAspect() const { return aspect; }
        inline float GetDepth() const { return depth; }
        inline bool GetOrthographic() const { return orthographic; }
        inline float GetOrthographicSize() const { return orthographicSize; }
        inline float GetFieldOfView() const { return fieldOfView; }
        inline float GetFarClipPlane() const { return farClipPlane; }
        inline float GetNearClipPlane() const { return nearClipPlane; }
        inline glm::vec2 GetViewportSize() { return viewportSize; }
        inline Rect GetRect() const { return rect; }

        void setDepth(float _depth) { depth = _depth; }
        void setOrthographic(bool _orthographic) { orthographic = _orthographic; UpdateProjectionMatrix(); Invalidate(); }
        void setOrthographicSize(float _orthographicSize) { orthographicSize = _orthographicSize; UpdateProjectionMatrix(); Invalidate(); }
        void setFieldOfView(float _fieldOfView)  { fieldOfView = _fieldOfView; UpdateProjectionMatrix(); Invalidate(); }
        void setFarClipPlane(float _farClipPlane) { farClipPlane = _farClipPlane; UpdateProjectionMatrix(); Invalidate(); }
        void setNearClipPlane(float _nearClipPlane) { nearClipPlane = _nearClipPlane; UpdateProjectionMatrix();  Invalidate(); }
        void setBackgroundColor(const Color& _color) { backgroundColor = _color; }
        inline void SetRect(const Rect& _rect) const { rect = _rect; }

        void UpdateProjectionMatrix();
        void UpdateViewMatrix();
        void Print();
        void Invalidate() { valid = false; }

    private:
        Color& backgroundColor;
        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;

        float aspect;
        bool valid = false;

        bool orthographic = true;
        float orthographicSize = 5.0f;
        float depth = 3.0f;
        float fieldOfView = 45.0f;
        float farClipPlane = 1000.0f;
        float nearClipPlane = 3.0f;

        glm::vec2 viewportSize = { 0.0f, 0.0f };
        Rect& rect;
    };

}  // namespace se
