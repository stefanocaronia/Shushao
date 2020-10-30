#include "sepch.h"

#include "Shushao/Core/Application.h"
#include "OrthographicCamera.h"

namespace Shushao {

    void OrthographicCamera::UpdateProjectionMatrix()
    {
        Window& window = Application::Get().GetWindow();

        if (aspect != window.GetAspect() || matrixInvalid) {
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

        matrixInvalid = false;
    }
}

