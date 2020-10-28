#include "sepch.h"

#include "Application.h"
#include "OrthographicCamera.h"

namespace Shushao {

    void OrthographicCamera::UpdateProjectionMatrix()
    {
        Window& window = Application::Get().GetWindow();
        valid = true;

        if (aspect != window.GetAspect() || !valid) {
            aspect = window.GetAspect();

            projectionMatrix = glm::ortho(
                -orthographicSize * aspect,
                orthographicSize * aspect,
                -orthographicSize,
                orthographicSize,
                nearClipPlane,
                farClipPlane);
            viewportSize = { orthographicSize * aspect * 2, orthographicSize * 2 };
        }
    }
}

