#include "sepch.h"

#include "Shushao/Core/Application.h"
#include "Shushao/Core/Config.h"
#include "Shushao/Core/Transform.h"
#include "Shushao/Core/Window.h"
#include "Camera.h"

namespace Shushao {

    Camera::Camera()
    {
        Init();
    }

    void Camera::UpdateViewMatrix()
    {
        //viewMatrix = glm::lookAt(transform->GetPosition(), Transform::FORWARD, Transform::UP); // mia
        viewMatrix = glm::inverse(transform->GetModelMatrix());
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void Camera::Update()
    {
        if (matrixInvalid) {
            UpdateProjectionMatrix();
            UpdateViewMatrix();
        }
    }

}  // namespace Shushao
