#include "sepch.h"

//#include <GLFW/glfw3.h>

#include "Shushao/Application.h"
#include "ImGuiLayer.h"
#include "Shushao/Application.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Shushao/Input/InputCodes.h"
#include "Shushao/Time.h"

namespace se {

    ImGuiLayer::ImGuiLayer() : Layer("ImGui Layer") {}

    ImGuiLayer::~ImGuiLayer()
    {

    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();


        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
        io.KeyMap[ImGuiKey_Tab] = SE_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = SE_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = SE_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = SE_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = SE_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = SE_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = SE_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = SE_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = SE_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = SE_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = SE_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = SE_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = SE_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = SE_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = SE_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = SE_KEY_A;
        io.KeyMap[ImGuiKey_C] = SE_KEY_C;
        io.KeyMap[ImGuiKey_V] = SE_KEY_V;
        io.KeyMap[ImGuiKey_X] = SE_KEY_X;
        io.KeyMap[ImGuiKey_Y] = SE_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = SE_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 430");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
        Application& app = Application::Get();

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        //float glfwTime = (float)glfwGetTime();
        //io.DeltaTime = time > 0.0f ? glfwTime - time : 1.0f / 60.0f;
        //time = glfwTime;

        io.DeltaTime = Time::deltaTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnImGuiRender()
    {

    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(SE_BIND_EVENT_FUNCTION(ImGuiLayer::onWindowResizedEvent));
    }

    bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.GetX(), event.GetY());

        return false;
    }

    bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += event.GetXOffset();
        io.MouseWheel += event.GetYOffset();

        return false;
    }

    bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;
        io.KeyCtrl = io.KeysDown[SE_KEY_LEFT_CONTROL] || io.KeysDown[SE_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[SE_KEY_LEFT_SHIFT] || io.KeysDown[SE_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[SE_KEY_LEFT_ALT] || io.KeysDown[SE_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[SE_KEY_LEFT_SUPER] || io.KeysDown[SE_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = false;
        return false;
    }

    bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = event.GetKeyCode();
        if (keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned short)keycode);

        return false;
    }

    bool ImGuiLayer::onWindowResizedEvent(WindowResizeEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        Application::Get().GetWindow().SetViewport(0, 0, event.GetWidth(), event.GetHeight());

        return false;
    }

}
