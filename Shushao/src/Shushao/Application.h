#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "LayerStack.h"

namespace Shushao {

    class Shader;
    class IndexBuffer;
    class VertexBuffer;
    class VertexArray;

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

        void Run();
        void Stop();

        inline static Application& Get() { return *instance; }
        inline Window& GetWindow() { return *window; }

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        // readonly properties
        const FT_Library& FreetypeLibrary = _freetypeLibrary;

    protected:
        virtual void Start(){};
        virtual void GetInput(){};
        virtual void Update(){};
        virtual void FixedUpdate(){};
        virtual void Render(){};
        virtual void End(){};

        bool RUNNING = true;
        bool READY = false;

        const FT_Library& freetypeLibrary = _freetypeLibrary;

    private:
        static Application* instance;
        std::unique_ptr<Window> window;
        ImGuiLayer* imGuiLayer;
        LayerStack layerStack;

        VertexArray* triangleVAO;
        VertexArray* squareVAO;
        Shader* shader;

        FT_Library _freetypeLibrary;

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

}  // Shushao
