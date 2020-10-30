#pragma once

#include "Object.h"
#include "Rect.h"
#include "RectTransform.h"

namespace Shushao {

    class Camera;
    class Entity;

    class Transform : public Object
    { 
    public:
        enum class Origin
        {
            LOCAL,
            WORLD
        };

        Transform();
        ~Transform();

        glm::vec3& GetLocalPosition() { return localPosition; }
        glm::quat& GetLocalRotation() { return localRotation; }
        glm::vec3& GetLocalScale() { return localScale; }
        glm::vec3& GetPosition() { return position; }
        glm::quat& GetRotation() { return rotation; }
        glm::vec3& GetScale() { return scale; }
        glm::vec3& GetPivot() { return pivot; }
        glm::vec3& GetForward() { return forward; }
        glm::vec3& GetRight() { return right; }
        glm::vec3& GetUp() { return up; }
        glm::vec3& GetVelocity() { return velocity; }
        glm::mat4& GetModelMatrix() { return modelMatrix; }
       
        float* GetUniformModelMatrix();  // Model Matrix for uniforms

        glm::mat4 GetLocalToParentMatrix();
        glm::mat4 GetLocalToWorldMatrix();
        glm::mat4 GetWorldToLocalMatrix();
        glm::mat4 GetRootMatrix();
        glm::vec3 GetWorldPosition();
        glm::vec3 GetLocalPosition(glm::vec3);
        glm::vec3 GetWorldScale();
        glm::quat GetWorldOrientation();

        // lifecycle
        void Init();
        void Update();

        glm::vec3 GetEulerAngles();
        glm::vec3 GetLocalEulerAngles();

        void SetPivot(glm::vec2);
        void SetPosition(glm::vec3);
        void SetLocalPosition(glm::vec3);
        void SetLocalRotation(glm::quat);
        void SetLocalRotation(glm::vec3);
        void SetLocalScale(glm::vec3);
        void SetRotation(glm::quat);
        void SetRotation(glm::vec3);

        void Invalidate();

        inline RectTransform* GetRectTransform() { return rectTransform; }
        inline void SetRectTransform(RectTransform* _rectTransform) { rectTransform = _rectTransform; }

        inline void SetEntity(Entity* _entity) { entity = _entity; }
        inline Entity* GetEntity() const { return entity; }

        inline bool IsRectTransform() const { return isRectTransform; }

        static const glm::mat4 MAT4_IDENTITY;
        static const glm::vec3 VEC3_ZERO;
        static const glm::vec3 VEC3_IDENTITY;
        static const glm::vec3 VEC3_IDENTITY2D;
        static const glm::vec3 UP;
        static const glm::vec3 DOWN;
        static const glm::vec3 FORWARD;
        static const glm::vec3 BACK;
        static const glm::vec3 RIGHT;
        static const glm::vec3 LEFT;
        static const glm::quat QUATERNION_IDENTITY;
        static const glm::vec3 AXIS_X;
        static const glm::vec3 AXIS_Y;
        static const glm::vec3 AXIS_Z;

    private:
        bool matrixInvalid = false;
        bool inverseMatrixInvalid = false;
        bool isRectTransform = false;
        bool isRoot = false;
        bool isFree = false;

        Origin origin = Origin::LOCAL;

        Entity* entity = nullptr;
        RectTransform* rectTransform = nullptr;

        glm::vec3 localPosition = VEC3_ZERO;
        glm::quat localRotation = QUATERNION_IDENTITY;
        glm::vec3 localScale = VEC3_IDENTITY;

        glm::vec3 position = VEC3_ZERO;
        glm::quat rotation = QUATERNION_IDENTITY;
        glm::vec3 scale = VEC3_IDENTITY2D;
        glm::vec3 velocity = VEC3_ZERO;
        glm::vec3 forward = FORWARD;
        glm::vec3 right = RIGHT;
        glm::vec3 up = UP;
        glm::vec3 pivot = VEC3_ZERO;
        glm::mat4 modelMatrix = glm::mat4();

        glm::mat4 localToWorldMatrix = glm::mat4();
        glm::mat4 localToParentMatrix = glm::mat4();
        glm::mat4 worldToLocalMatrix = glm::mat4();
        glm::mat4 rootMatrix = glm::mat4();

        glm::vec3 lastPosition = VEC3_ZERO;

        void setupDirections();
        void updateRectTransforms();
    };

}  // namespace Shushao
