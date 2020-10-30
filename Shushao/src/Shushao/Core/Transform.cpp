#include "sepch.h"

//#include "Canvas.h"
#include "Shushao/Renderer/Color.h"
#include "Entity.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Shushao/Nodes/Camera.h"

namespace Shushao {

    const glm::mat4 Transform::MAT4_IDENTITY = glm::mat4();
    const glm::vec3 Transform::VEC3_ZERO = { 0.0f, 0.0f, 0.0f };
    const glm::vec3 Transform::VEC3_IDENTITY = { 1.0f, 1.0f, 1.0f };
    const glm::vec3 Transform::VEC3_IDENTITY2D = { 1.0f, 1.0f, 0.0f };
    const glm::vec3 Transform::UP = { 0.0f, 1.0f, 0.0f };
    const glm::vec3 Transform::AXIS_X = { 1.0f, 0.0f, 0.0f };
    const glm::vec3 Transform::AXIS_Y = { 0.0f, 1.0f, 0.0f };
    const glm::vec3 Transform::AXIS_Z = { 0.0f, 0.0f, 1.0f };
    const glm::vec3 Transform::DOWN = { 0.0f, -1.0f, 0.0f };
    const glm::vec3 Transform::FORWARD = { 0.0f, 0.0f, 1.0f };
    const glm::vec3 Transform::BACK = { 0.0f, 0.0f, -1.0f };
    const glm::vec3 Transform::RIGHT = { 1.0f, 0.0f, 0.0f };
    const glm::vec3 Transform::LEFT = { -1.0f, 0.0f, 0.0f };
    const glm::quat Transform::QUATERNION_IDENTITY = { 1.0f, 0.0f, 0.0f, 0.0f };

    /*
        MVP = P * V * M; 
		MV = V * M; 
		VP = P * V;     
    */

    Transform::Transform()
    {
        rectTransform = new RectTransform(this);
    }

    Transform::~Transform()
    {
        delete (rectTransform);
        rectTransform = nullptr;
    }

    void Transform::Invalidate()
    {
        if (!matrixInvalid) {
            matrixInvalid = true;
            inverseMatrixInvalid = true;
        }

        Entity* owner = ((Entity*)GetOwner());
        for (Node* child : owner->GetChildren()) {
            if (child->HasTransform()) {
                ((Entity*)child)->GetTransform()->Invalidate();
                /// TODO: se ci sono nodi non entity in mezzo si ferma la ricorsione
            }
        }
        
        if (owner->is<Camera>()) {
            ((Camera*)owner)->InvalidateMatrix();
        }
    }

    //{ #region position

    void Transform::SetPosition(glm::vec3 position_)
    {
        Entity* owner = ((Entity*)GetOwner());

        if (owner->IsRoot()) return;

        origin = Origin::WORLD;
        Invalidate();
        localPosition = owner->IsAtRoot() ? position_ : owner->GetTransform()->position - position_;
        position = position_;

        if (isRectTransform) {
            rectTransform->update();
        }

        setupDirections();
    }

    void Transform::SetLocalPosition(glm::vec3 position_)
    {
        if (entity->IsRoot()) return;
        origin = Origin::LOCAL;
        localPosition = position_;
        Invalidate();
        position = GetWorldPosition();

        if (isRectTransform) {
            rectTransform->update();
        }

        setupDirections();
    }

    void Transform::SetLocalRotation(glm::vec3 angles_)
    {  // angles_ is in radians
        if (entity->IsRoot()) return;
        origin = Origin::LOCAL;
        localRotation = glm::quat(angles_ * DEGTORAD);
        Invalidate();
        rotation = GetWorldOrientation();
        setupDirections();
    }

    void Transform::SetLocalRotation(glm::quat rotation_)
    {
        if (entity->IsRoot()) return;
        origin = Origin::LOCAL;
        localRotation = rotation_;
        Invalidate();
        rotation = GetWorldOrientation();
        setupDirections();
    }

    void Transform::SetRotation(glm::vec3 angles_)
    {  // angles_ is in radians
        if (entity->IsRoot()) return;
        origin = Origin::WORLD;
        rotation = glm::quat(angles_ * DEGTORAD);
        //localRotation = rotation;
        setupDirections();
    }

    void Transform::SetRotation(glm::quat rotation_)
    {
        if (entity->IsRoot()) return;
        origin = Origin::WORLD;
        rotation = rotation_;
        Invalidate();
        setupDirections();
    }

    glm::vec3 Transform::GetEulerAngles()
    {
        return glm::eulerAngles(rotation) * RADTODEG;
    }

    glm::vec3 Transform::GetLocalEulerAngles()
    {
        return glm::eulerAngles(localRotation) * RADTODEG;
    }

    void Transform::setupDirections()
    {
        up = rotation * UP;
        right = rotation * RIGHT;
        forward = rotation * FORWARD;
    }

    void Transform::SetLocalScale(glm::vec3 scale_)
    {
        if (entity->IsRoot()) return;
        localScale = scale_;
        scale = GetWorldScale();
    }

    void Transform::SetPivot(glm::vec2 pivot_)
    {
        if (entity->IsRoot()) return;
        pivot = { pivot_.x, pivot_.y, 0.0f };
        rectTransform->SetPivot({ pivot.x, pivot.y });
    }

    float* Transform::GetUniformModelMatrix()
    {
        return &modelMatrix[0][0];
    }

    void Transform::Init()
    {
        Invalidate();

        // da ripristinare
        //rectTransform->init();
    }

    void Transform::Update()
    {
        if (origin == Origin::LOCAL) {
            position = GetWorldPosition();
            rotation = GetWorldOrientation();
        }

        if (isRectTransform) {
            rectTransform->update();
        }

        modelMatrix = GetLocalToWorldMatrix();

        setupDirections();

        velocity = (1 / Time::Delta) * (position - lastPosition);
        lastPosition = position;
    }

    glm::mat4 Transform::GetLocalToParentMatrix()
    {
        Entity* parent = entity->GetParentEntity();

        if (isRectTransform && parent->GetTransform()->IsRectTransform()) {
            localToParentMatrix = rectTransform->GetLocalToParentMatrix();
        } else {
            localToParentMatrix = glm::translate(glm::mat4(), localPosition) * glm::toMat4(localRotation) * glm::scale(glm::mat4(), localScale);
        }
        return localToParentMatrix;
    }

    glm::mat4 Transform::GetRootMatrix()
    {
        return glm::translate(glm::mat4(), position) * glm::toMat4(rotation) * glm::scale(glm::mat4(), localScale);
    }

    glm::mat4 Transform::GetLocalToWorldMatrix()
    {
        if (matrixInvalid) {
            if (origin == Origin::WORLD) {
                localToWorldMatrix = GetRootMatrix();
            } else if (entity->IsAtRoot()) {
                localToWorldMatrix = GetLocalToParentMatrix();
            } else {
                localToWorldMatrix = entity->GetParentEntity()->GetTransform()->GetLocalToWorldMatrix() * GetLocalToParentMatrix();
            }
            matrixInvalid = false;
        }
        return localToWorldMatrix;
    }

    glm::mat4 Transform::GetWorldToLocalMatrix()
    {
        /*if (inverseMatrixInvalid) {
                _worldToLocalMatrix = glm::inverse(GetLocalToWorldMatrix());
                inverseMatrixInvalid = false;
            }
            return _worldToLocalMatrix;*/

        if (inverseMatrixInvalid) {
            Entity* parent = entity->GetParentEntity();
            if (entity->IsAtRoot()) {
                worldToLocalMatrix = glm::mat4();
            } else if (parent) {
                std::shared_ptr<Transform> transform = parent->GetTransform();
                worldToLocalMatrix = glm::toMat4(transform->rotation) * glm::translate(glm::mat4(), -transform->position);
            }
            inverseMatrixInvalid = false;
        }
        return worldToLocalMatrix;
    }

    glm::vec3 Transform::GetWorldPosition()
    {
        glm::vec4 p = GetLocalToWorldMatrix() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        return glm::vec3(p.x, p.y, p.z);
    }

    glm::vec3 Transform::GetLocalPosition(glm::vec3 position_)
    {
        glm::vec4 p = GetWorldToLocalMatrix() * glm::vec4(position_.x, position_.y, position_.z, 1.0f);
        return glm::vec3(p.x, p.y, p.z);
    }

    glm::vec3 Transform::GetWorldScale()
    {
        if (!entity->IsAtRoot()) {
            Entity* parent = entity->GetParentEntity();
            if (parent != nullptr) {
                return localScale * parent->GetTransform()->GetWorldScale();
            }
        }

        return localScale;
    }

    glm::quat Transform::GetWorldOrientation()
    {
        if (!entity->IsAtRoot()) {
            Entity* parent = entity->GetParentEntity();
            if (parent != nullptr) {
                return localRotation * parent->GetTransform()->rotation;
            }

        }
        return localRotation;
    }

}  // namespace Shushao
