#pragma once

#include "Shushao/Layer.h"
#include "Shushao/Events/KeyEvent.h"
#include "Shushao/Events/MouseEvent.h"
#include "Shushao/Events/ApplicationEvent.h"

namespace se {

    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnImGuiRender();
        void OnEvent(Event& event);

    private:
        float time = 0.0f;

        bool onMouseButtonPressedEvent(MouseButtonPressedEvent& event);
        bool onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
        bool onMouseMovedEvent(MouseMovedEvent& event);
        bool onMouseScrolledEvent(MouseScrolledEvent& event);
        bool onKeyPressedEvent(KeyPressedEvent& event);
        bool onKeyReleasedEvent(KeyReleasedEvent& event);
        bool onKeyTypedEvent(KeyTypedEvent& event);
        bool onWindowResizedEvent(WindowResizeEvent& event);

    };
}

