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
        DEBUG_INFO("Received event {0} ", event);
        event.Handled = true;
    }
};

class Game : public Application
{
    bool perspectiveTest = false;

    void Configure()
    {
        PushLayer(new TestLayer());
        DEBUG_INFO("In Configuration");
    }

    void Awake()
    {
        DEBUG_INFO("Application is Awake");
    }

    void GetInput() override
    {}
};

se::Application* se::CreateApplication()
{
    return new Game();
}
