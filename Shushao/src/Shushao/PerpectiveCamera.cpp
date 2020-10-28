#include "sepch.h"

#include "Application.h"
#include "PerpectiveCamera.h"

namespace Shushao {

    void PerpectiveCamera::UpdateProjectionMatrix()
    {
        Window& window = Application::Get().GetWindow();

        valid = true;

        if (aspect != window.GetAspect() || !valid) {
            aspect = window.GetAspect();

            projectionMatrix = glm::perspective(
                fieldOfView,
                aspect,
                nearClipPlane,
                farClipPlane);
        }
    }

}