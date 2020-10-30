#include "sepch.h"

#include <glad/glad.h>

#include "Config.h"
#include "Shushao/Events/ApplicationEvent.h"
#include "Font.h"
#include "Shushao/Input/Input.h"
#include "Resources.h"
#include "Time.h"
#include "Platform/OpenGL/OpenGL.h"
#include "Shushao/Renderer/Shader.h"
#include "Application.h"
#include "Shushao/Renderer/VertexBuffer.h"
#include "Shushao/Renderer/IndexBuffer.h"
#include "Shushao/Renderer/BufferLayout.h"
#include "Shushao/Renderer/VertexArray.h"
#include "Shushao/Renderer/Renderer.h"
#include "Shushao/Renderer/RenderCommand.h"

namespace Shushao {

    Application* Application::instance = nullptr;

    Application::Application()
    {
        SE_CORE_ASSERT(!instance, "Application already exists!");

        instance = this;

        Debug::Initialize();

        loadConfiguration();

        initializeLibraries();
        initializeWindow();
        initializeTime();

        imGuiLayer = new ImGuiLayer();
        PushOverlay(imGuiLayer);

        initializePhysics();
        initializeInput();
        loadEngineResources();

        //System::Init(); // Init System services

        //initializeScene();

        //if (SceneManager::activeScene != nullptr) {
        //    Camera* activeCamera = SceneManager::activeScene->activeCamera;
        //    window->Clear(activeCamera->backgroundColor.r, activeCamera->backgroundColor.g, activeCamera->backgroundColor.b, 1.0f, 1.0f);
        //} else {
        //    window->Clear();
        //}

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    }

    void Application::render()
    {
        Time::RenderTime = Time::GetTime();
        window->Clear();
        //SceneManager::activeScene->render();

        RenderCommand::Clear();

        imGuiLayer->Begin();
        for (Layer* layer : layerStack) {
            layer->OnUpdate();
            //layer->OnImGuiRender();
        }
        imGuiLayer->End();

        //Render();  // (derived)
        //SceneManager::activeScene->renderOverlay();
        // if (Physics::enabled && Physics::debug) ((b2World*)Physics::GetWorld())->DrawDebugData();
        window->Update();
        Time::FrameCount++;
    }

    void Application::update()
    {
        Time::RealtimeSinceStartup = Time::GetTime();
        layerStack.Update();
        // Input::update();  // Update Input Service
        //System::Update();  // update dei system services
        //SceneManager::activeScene->update();
        //Update();  // (derived)
    }

    void Application::fixed()
    {
        Time::FixedTime = Time::GetTime();
        Time::InFixedTimeStep = true;
        //if (Physics::enabled) Physics::Update();
        //SceneManager::activeScene->fixed();
        FixedUpdate();  // (derived)
        Time::InFixedTimeStep = false;
    }

    void Application::exit()
    {
        End();  // (derived)
        //SceneManager::activeScene->exit();
        // Input::exit();
        //System::Exit();
        //Physics::Exit();
        //SceneManager::Clear();
        Resources::Clear();
        //System::Clear();
    }

    void Application::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(SE_BIND_EVENT_FUNCTION(Application::onWindowClose));

        //DEBUG_CORE_TRACE("Event {0}", event);

        for (auto it = layerStack.end(); it != layerStack.begin();) {
            (*--it)->OnEvent(event);
            if (event.Handled) {
                break;
            }
        }
    }

    Application::~Application()
    {
        DEBUG_CORE_INFO("Application Destructor");
    }

    void Application::loadConfiguration()
    {
        SE_CORE_ASSERT(Config::LoadEngineConfig(), "Error Initializing Engine Configuration");
        SE_CORE_ASSERT(Config::LoadUserConfig(), "Error Initializing User Configuration");
    }

    void Application::initializeLibraries()
    {
        FT_Init_FreeType(&_freetypeLibrary);
    }

    void Application::initializeWindow()
    {
        window = std::unique_ptr<Window>(Window::Create({ Config::title, Config::displayWidth, Config::displayHeight, Config::fullscreen }));
        window->SetEventCallback(SE_BIND_EVENT_FUNCTION(Application::OnEvent));
    }

    void Application::initializeTime()
    {
        // Time init
        Time::SetFrameRateLimit(Config::Time::frameRateLimit);
        Time::SetFixedRateLimit(Config::Time::fixedRateLimit);
    }

    void Application::initializeInput()
    {
        // Init Input service
        // Input::init();
    }

    void Application::loadEngineResources()
    {
        // Load engine resources
        Resources::Load<Font>("consolas", FONT_CONSOLAS, LIB_SHUSHAO);
    }

    void Application::initializeScene()
    {
        //SE_CORE_ASSERT(SceneManager::activeScene != nullptr, "Active Scene not set");

        //// init all entities
        //SceneManager::activeScene->ScanEntities();
        //SceneManager::activeScene->ScanActiveComponents();
        //SceneManager::activeScene->Init();  // vengono chiamati qui gli Init di tutti gli oggetti attivi

        //if (Debug::enabled) {
        //    SceneManager::activeScene->PrintHierarchy();
        //    SceneManager::activeScene->PrintActiveComponentsInScene();
        //    SceneManager::activeScene->PrintActiveRenderersInScene();
        //    SceneManager::activeScene->PrintActiveLightsInScene();
        //    System::ListServices();
        //    SceneManager::activeScene->activeCamera->print();
        //    Resources::toString();
        //    Config::Layers.toString("Layers");
        //    Config::SortingLayers.toString("SortingLayers");
        //}
    }

    void Application::initializePhysics()
    {
        // Physics 2d init
        /*if (Config::Physics::enabled) {
            if (!Physics::Init()) {
                DEBUG_CORE_ERROR("Error Initializing Physics");
            }
        }*/
    }

    void Application::Run()
    {
        //if (!SceneManager::sceneSet)
        //    return;

        // Start method (derived)
        Start();

        while (RUNNING) {
            Time::Update();

            //std::thread tInput;
            //std::thread tUpdate;
            //std::thread tFixed;

            // scan scene (se invalid) e init objects
            //scan();

            // Process input method (derived)
            //tInput = std::thread(&Application::GetInput, this);
            GetInput();

            // Update Application
            //tUpdate = std::thread(&Application::update, this);
            update();

            if (Time::FixedDeltaTime >= Time::FixedLimitDuration) {
                // Fixed Update Application (physics)
                //tFixed = std::thread(&Application::fixed, this);
                fixed();
            }

            //if (tInput.joinable()) tInput.join();
            //if (tUpdate.joinable()) tUpdate.join();
            //if (tFixed.joinable()) tFixed.join();

            if (Config::Time::frameRateLimit == 0 || (Time::RenderDeltaTime >= Time::FrameLimitDuration)) {
                render(); // Main render cycle
            }
        }

        exit();
    }

    void Application::Stop()
    {
        RUNNING = false;
    }

    void Application::scan()
    {
        //return;
        //if (SceneManager::activeScene->Invalid) {
        //    SceneManager::activeScene->ScanEntities();
        //    SceneManager::activeScene->ScanActiveComponents();
        //}

        //// chiamo awake di tutti i componenti non ancora svegli
        //SceneManager::activeScene->Init();
    }

    void Application::PushLayer(Layer* layer)
    {
        layerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* layer)
    {
        layerStack.PushOverlay(layer);
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        RUNNING = false;
        return true;
    }

}  // Shushao