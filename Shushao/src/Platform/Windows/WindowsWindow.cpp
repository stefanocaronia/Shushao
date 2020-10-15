#include "sepch.h"

#include "WindowsWindow.h"
#include "Shushao/Core.h"
#include "Shushao/Config.h"
#include "Shushao/Debug.h"
#include "Shushao/Events/ApplicationEvent.h"
#include "Shushao/Events/KeyEvent.h"
#include "Shushao/Events/MouseEvent.h"
#include "Shushao/OpenGLCore.h"

namespace se {

    static bool GLFWInitialized = false;

    Window* Window::Create(const WindowProps& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
    {
        initialize(props);
        Clear();
        setGlfwCallbacks();
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown();
    }

    void WindowsWindow::initialize(const WindowProps& props)
    {
        data.Title = props.Title;
        data.Width = props.Width;
        data.Height = props.Height;
        data.Fullscreen = props.Fullscreen;

        DEBUG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!GLFWInitialized) {
            int success = glfwInit();
            SE_CORE_ASSERT(success, "Could not intialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        window = glfwCreateWindow(
            (int)props.Width,
            (int)props.Height,
            data.Title.c_str(),
            (data.Fullscreen ? glfwGetPrimaryMonitor() : nullptr),
            nullptr  //
        );

        glfwMakeContextCurrent(window);

        // init Glad
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SE_CORE_ASSERT(status, "Failed to initialize Glad!");

        glfwSetWindowUserPointer(window, &data);
        SetVSync(true);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        desktopWidth = mode->width;
        desktopHeight = mode->height;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);  // questo per il 2d
        glViewport(0, 0, GetWidth(), GetHeight());
    }

    void WindowsWindow::setGlfwCallbacks()
    {
        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::shutdown() const
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void WindowsWindow::Update() const
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return data.VSync;
    }

    void WindowsWindow::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearDepth(1.0f);
        GLClearError();
    }

    void WindowsWindow::Clear(float r, float g, float b, float a, float depth = 1.0f) const
    {
        glClearColor(r, g, b, a);
        glClearDepth(depth);
        GLClearError();
    }

    void WindowsWindow::SetFullscreen(bool fs)
    {
        fullscreen = fs;

        // TODO
    #if 0
        if (fullscreen) {
            SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
            glViewport(0, 0, DESKTOP_WIDTH, DESKTOP_HEIGHT);
        } else {
            SDL_SetWindowFullscreen(gWindow, SDL_FALSE);
            SDL_GetWindowSize(gWindow, (int*)&WIDTH, (int*)&HEIGHT);
            glViewport(0, 0, WIDTH, HEIGHT);
        }
    #endif
    }

    void WindowsWindow::ToggleFullscreen()
    {
        SetFullscreen(!fullscreen);
    }

    void WindowsWindow::Swap() const
    {
        glfwSwapBuffers(window);
    }

    void WindowsWindow::Reset() const
    {
        Clear();
    }
}  // namespace se
