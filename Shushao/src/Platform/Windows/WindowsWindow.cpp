#include "sepch.h"

#include "WindowsWindow.h"
#include "Shushao/Events/ApplicationEvent.h"
#include "Shushao/Events/KeyEvent.h"
#include "Shushao/Events/MouseEvent.h"

namespace se {

    static bool GLFWInitialized = false;

    Window* Window::Create(const WindowProperties& props)
    {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProperties& props)
    {
        initialize(props);
        inizializeGLFW();
        retrieveDesktopSize();
        initializeGlad();
        initializeOpenGL();
        setGlfwCallbacks();
        Clear();
    }

    WindowsWindow::~WindowsWindow()
    {
        shutdown();
    }

    void WindowsWindow::initialize(const WindowProperties& windowProperties)
    {
        title = windowProperties.Title;
        width = windowProperties.Width;
        height = windowProperties.Height;
        fullscreen = windowProperties.Fullscreen;

    }

    void WindowsWindow::initializeOpenGL()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);  // questo per il 2d
        glViewport(0, 0, GetWidth(), GetHeight());
    }

    void WindowsWindow::initializeGlad()
    {
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SE_CORE_ASSERT(status, "Failed to initialize Glad!");
    }

    void WindowsWindow::inizializeGLFW()
    {
        DEBUG_CORE_INFO("Creating window {0} ({1}, {2})", title, width, height);

        if (!GLFWInitialized) {
            int success = glfwInit();
            SE_CORE_ASSERT(success, "Could not intialize GLFW!");
            glfwSetErrorCallback(GLFWErrorCallback);
            GLFWInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        monitor = glfwGetPrimaryMonitor();

        window = glfwCreateWindow((int)width, (int)height, title.c_str(), (fullscreen ? monitor : nullptr), nullptr);

        glfwMakeContextCurrent(window);

        glfwSetWindowUserPointer(window, this);
        SetVSync(true);
    }

    void WindowsWindow::retrieveDesktopSize()
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        desktopWidth = mode->width;
        desktopHeight = mode->height;
    }

    void WindowsWindow::setGlfwCallbacks()
    {
        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);
            windowObject.SetWidth(width);
            windowObject.SetHeight(height);

            WindowResizeEvent event(width, height);
            windowObject.Callback(event);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            windowObject.Callback(event);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    windowObject.Callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    windowObject.Callback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    windowObject.Callback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            windowObject.Callback(event);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);

            switch (action) {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    windowObject.Callback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    windowObject.Callback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            windowObject.Callback(event);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            Window& windowObject = *(Window*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            windowObject.Callback(event);
        });
    }

    void WindowsWindow::shutdown() const
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        vSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return vSync;
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

    void WindowsWindow::Update() const
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
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
