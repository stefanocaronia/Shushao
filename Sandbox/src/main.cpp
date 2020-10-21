#include <Shushao.h>

using namespace Shushao;

class TestLayer : public Shushao::Layer
{
public:
    TestLayer() : Shushao::Layer("Layer di test") {}

    void OnUpdate() override
    {
        if (Input::IsKeyPressed(SE_KEY_A)) {
            DEBUG_INFO("Hai premuto A!");
        }
    }

    void OnEvent(Shushao::Event& event) override
    {
        //DEBUG_INFO("Received event {0} ", event);
        event.Handled = true;
    }
};

class Sandbox : public Shushao::Application
{
public:

    Sandbox()
    {
        PushLayer(new TestLayer());
    }
};

Shushao::Application* Shushao::CreateApplication()
{
    return new Sandbox();
}
