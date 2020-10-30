#include "sepch.h"

#include "Shushao/Core/Application.h"
#include "PerpectiveCamera.h"

namespace Shushao {

    void PerpectiveCamera::UpdateProjectionMatrix()
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