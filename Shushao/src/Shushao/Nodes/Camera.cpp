#include "sepch.h"

#include "Shushao/Core/Application.h"
#include "Shushao/Core/Config.h"
#include "Shushao/Core/Transform.h"
#include "Shushao/Core/Window.h"
#include "Camera.h"

namespace Shushao {

    void Camera::UpdateViewMatrix()
    {
        //viewMatrix = glm::lookAt(transform->GetLocalPosition(), Transform::FORWARD, Transform::UP); // mia
        viewMatrix = glm::inverse(transform->GetModelMatrix());
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

}  // namespace Shushao
