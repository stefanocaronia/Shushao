#include "sepch.h"

#include "Application.h"
#include "Config.h"
#include "Transform.h"
#include "Camera.h"
#include "Window.h"

namespace Shushao {

    void Camera::Init()
    {
        UpdateProjectionMatrix();
    }

    void Camera::UpdateProjectionMatrix()
    {
        Window& window = Application::Get().GetWindow();

        if (aspect != window.GetAspect() || !valid) {
            aspect = window.GetAspect();

            if (orthographic) {
                projectionMatrix = glm::ortho(
                    -orthographicSize * aspect,
                    orthographicSize * aspect,
                    -orthographicSize,
                    orthographicSize,
                    nearClipPlane,
                    farClipPlane);
                viewportSize = { orthographicSize * aspect * 2, orthographicSize * 2 };
            } else {
                projectionMatrix = glm::perspective(
                    fieldOfView, 
                    aspect, 
                    nearClipPlane, 
                    farClipPlane);
            }
        }

        valid = true;
    }

    void Camera::UpdateViewMatrix()
    {
        viewMatrix = glm::lookAt(transform->localPosition, Transform::FORWARD, Transform::UP);
    }

    void Camera::Print()
    {
        Logger::setColor(ConsoleColor::CYAN);

        std::cout << " Camera " << name << std::endl;

        std::cout << "  - "
            << "backgroundColor: " << backgroundColor.r << " " << backgroundColor.g << " " << backgroundColor.b << " " << backgroundColor.a << std::endl;
        std::cout << "  - "
            << "aspect: " << aspect << std::endl;
        std::cout << "  - "
            << "orthographic: " << (orthographic ? "true" : "false") << std::endl;
        std::cout << "  - "
            << "orthographicSize: " << orthographicSize << std::endl;
        std::cout << "  - "
            << "depth: " << depth << std::endl;
        std::cout << "  - "
            << "fieldOfView: " << fieldOfView << std::endl;
        std::cout << "  - "
            << "farClipPlane: " << farClipPlane << std::endl;
        std::cout << "  - "
            << "nearClipPlane: " << nearClipPlane << std::endl;
        std::cout << "  - "
            << "rect: " << rect.x << " " << rect.y << " " << rect.width << " " << rect.height << std::endl;

        Logger::setColor(ConsoleColor::LIGHTGREY);
    }
}  // namespace se
