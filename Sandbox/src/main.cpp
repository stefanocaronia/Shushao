#include <Shushao.h>

using namespace se;

class TestLayer : public se::Layer
{
public:
    TestLayer() : Layer("Layer di test") {}

    void OnUpdate() override
    {
        //DEBUG_INFO("{0} Update", GetName());
    }

    void OnEvent(se::Event& event) override
    {
        //DEBUG_INFO("Received event {0} ", event);
        event.Handled = true;
    }
};

class Sandbox : public Application
{
public:

    Sandbox()
    {
        PushLayer(new TestLayer());
        PushOverlay(new ImGuiLayer());
    }
};

se::Application* se::CreateApplication()
{
    return new Sandbox();
}
