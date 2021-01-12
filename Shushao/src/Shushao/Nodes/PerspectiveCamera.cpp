#include "sepch.h"

#include "Shushao/Core/Application.h"
#include "PerspectiveCamera.h"

namespace Shushao {

    void PerspectiveCamera::UpdateProjectionMatrix()
    {
        Window& window = Application::Get().GetWindow();

        if (aspect != window.GetAspect() || matrixInvalid) {
            aspect = window.GetAspect();

            projectionMatrix = glm::perspective(
                fieldOfView,
                aspect,
                nearClipPlane,
                farClipPlane);
        }

        matrixInvalid = false;
    }

}