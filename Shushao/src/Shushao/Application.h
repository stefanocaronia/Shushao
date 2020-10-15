#pragma once

#include "sepch.h"
#include "Shushao/Core.h"

#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace se {

class Application {
public:
    static Application* instance;

    enum class Stage {
        INIT,
        UPDATE,
        FIXED,
        RENDER,
        EXIT
    };

    virtual ~Application();

    std::string name;

    void Initialize();
    void Run();
    void Stop();

    inline static Application& Get() { return *instance; }
    inline Window& GetWindow() { return *window; }

    void OnEvent(Event& e);

protected:
    virtual void Configure() = 0;
    virtual void Awake() = 0;
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
    Window* window;

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

    bool onWindowClose(WindowCloseEvent& e);
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace se
