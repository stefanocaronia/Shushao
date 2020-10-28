#include "sepch.h"

#include "Application.h"
#include "Config.h"
#include "Transform.h"
#include "Camera.h"
#include "Window.h"

namespace Shushao {

    void Camera::UpdateViewMatrix()
    {
        viewMatrix = glm::lookAt(transform->GetLocalPosition(), Transform::FORWARD, Transform::UP);
    }

}  // namespace se
