#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace se {

class Application {
public:
    enum class Stage {
        INIT,
        UPDATE,
        FIXED,
        RENDER,
        EXIT
    };

    Application();
    virtual ~Application();

    std::string name;

    void Initialize();
    void Run();
    void Stop();

    inline static Application& Get() { return *instance; }
    inline Window& GetWindow() { return *window; }

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

protected:
    virtual void Start() {};
    virtual void GetInput() {};
    virtual void Update() {};
    virtual void FixedUpdate() {};
    virtual void Render() {};
    virtual void End() {};

    bool RUNNING = true;
    bool READY = false;

    bool keys[350];

private:
    static Application* instance;
    Window* window;
    LayerStack layerStack;

    void scan();
    void update();
    void render();
    void fixed();
    void exit();

    void initializePhysics();
    void loadConfiguration();
    void initializeWindow();
    void initializeTime();
    void initializeInput();
    void loadEngineResources();
    void initializeScene();
    void initializeLibraries();

    bool onWindowClose(WindowCloseEvent& e);
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace se
