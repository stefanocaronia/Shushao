#include "Precompiled.h"

#include "GameData.h"
#include "Application.h"
#include "Core/Config.h"
#include "Design.h"
#include "Events/ApplicationEvent.h"
#include "Font.h"
#include "Input.h"
#include "Physics/Physics.h"
#include "Resources.h"
#include "SceneManager.h"
#include "System.h"
#include "Time.h"

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace se {

    Application* Application::instance = nullptr;

    Application::~Application()
    {
        DEBUG_CORE_INFO("Application Destructor");
    }

    void Application::Initialize()
    {
        GameData::Application = this;
        Debug::Initialize();

        loadConfiguration();

        Configure(); // (derived) ovverride configuration

        initializeLibraries();
        initializeWindow();
        initializeTime();
        initializePhysics();
        initializeInput();
        loadEngineResources();

        System::Init(); // Init System services

        Awake(); // (derived)

        initializeScene();

        Camera* activeCamera = SceneManager::activeScene->activeCamera;
        window->Clear(activeCamera->backgroundColor.r, activeCamera->backgroundColor.g, activeCamera->backgroundColor.b, 1.0f, 1.0f);
    }

    void Application::loadConfiguration()
    {
        SE_CORE_ASSERT(Config::LoadEngineConfig(), "Error Initializing Engine Configuration");
        SE_CORE_ASSERT(Config::LoadUserConfig(), "Error Initializing User Configuration");
    }

    void Application::initializeLibraries()
    {
        FT_Init_FreeType(&GameData::freetypeLibrary);
    }

    void Application::initializeWindow()
    {
        window = Window::Create({ Config::title, Config::displayWidth, Config::displayHeight, Config::fullscreen });
        window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
        GameData::Window = window;
    }

    void Application::initializeTime()
    {
        // Time init
        Time::setFrameRateLimit(Config::Time::frameRateLimit);
        Time::setFixedRateLimit(Config::Time::fixedRateLimit);
    }


    void Application::initializeInput()
    {
        // Init Input service
        // Input::init();
        for (bool& k : keys) {
            k = false;
        }
    }

    void Application::loadEngineResources()
    {
        // Load engine resources
        Resources::Load<Font>("consolas", FONT_CONSOLAS, LIB_SHUSHAO);
    }

    void Application::initializeScene()
    {
        SE_CORE_ASSERT(SceneManager::activeScene != nullptr, "Active Scene not set");

        // init all entities
        SceneManager::activeScene->ScanEntities();
        SceneManager::activeScene->ScanActiveComponents();
        SceneManager::activeScene->Init();  // vengono chiamati qui gli Awake di tutti gli oggetti attivi

        if (Debug::enabled) {
            SceneManager::activeScene->PrintHierarchy();
            SceneManager::activeScene->PrintActiveComponentsInScene();
            SceneManager::activeScene->PrintActiveRenderersInScene();
            SceneManager::activeScene->PrintActiveLightsInScene();
            System::ListServices();
            SceneManager::activeScene->activeCamera->print();
            Resources::toString();
            Config::Layers.toString("Layers");
            Config::SortingLayers.toString("SortingLayers");
        }
    }

    void Application::initializePhysics()
    {
        // Physics 2d init
        if (Config::Physics::enabled) {
            if (!Physics::Init()) {
                DEBUG_CORE_ERROR("Error Initializing Physics");
            }
        }
    }

    void Application::Run()
    {
        if (!SceneManager::sceneSet)
            return;

        // Start method (derived)
        Start();

        while (RUNNING) {
            Time::Update();

            //std::thread tInput;
            //std::thread tUpdate;
            //std::thread tFixed;

            // scan scene (se invalid) e init objects
            scan();

            // Process input method (derived)
            //tInput = std::thread(&Application::GetInput, this);
            GetInput();

            // Update Application
            //tUpdate = std::thread(&Application::update, this);
            update();

            if (Time::fixedDeltaTime >= Time::fixedLimitDuration) {
                // Fixed Update Application (physics)
                //tFixed = std::thread(&Application::fixed, this);
                fixed();
            }

            //if (tInput.joinable()) tInput.join();
            //if (tUpdate.joinable()) tUpdate.join();
            //if (tFixed.joinable()) tFixed.join();

            if (Config::Time::frameRateLimit == 0 || (Time::renderDeltaTime >= Time::frameLimitDuration)) {
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
        if (SceneManager::activeScene->Invalid) {
            SceneManager::activeScene->ScanEntities();
            SceneManager::activeScene->ScanActiveComponents();
        }

        // chiamo awake di tutti i componenti non ancora svegli
        SceneManager::activeScene->Init();
    }

    void Application::render()
    {
        Time::renderTime = Time::GetTime();
        window->Clear();
        SceneManager::activeScene->render();
        Render();  // (derived)
        SceneManager::activeScene->renderOverlay();
        // if (Physics::enabled && Physics::debug) ((b2World*)Physics::GetWorld())->DrawDebugData();

        window->Update();
        Time::frameCount++;
    }

    void Application::update()
    {
        Time::realtimeSinceStartup = Time::GetTime();
        // Input::update();  // Update Input Service
        System::update();  // update dei system services
        SceneManager::activeScene->update();
        Update();  // (derived)
    }

    void Application::fixed()
    {
        Time::fixedTime = Time::GetTime();
        Time::inFixedTimeStep = true;
        if (Physics::enabled) Physics::Update();
        SceneManager::activeScene->fixed();
        FixedUpdate();  // (derived)
        Time::inFixedTimeStep = false;
    }

    void Application::exit()
    {
        End();  // (derived)
        SceneManager::activeScene->exit();
        // Input::exit();
        System::exit();
        Physics::Exit();
        SceneManager::Clear();
        Resources::Clear();
        System::Clear();
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(onWindowClose));
    }

    bool Application::onWindowClose(WindowCloseEvent& e)
    {
        RUNNING = false;
        return true;
    }

}  // namespace se
