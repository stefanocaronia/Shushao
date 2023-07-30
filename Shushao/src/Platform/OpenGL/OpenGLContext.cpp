#include "sepch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Shushao/Core/Window.h"
#include "OpenGLContext.h"

namespace Shushao {

    OpenGLContext::OpenGLContext(GLFWwindow* _window) : window(_window)
    {
        SE_CORE_ASSERT(_window, "Window is null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SE_CORE_ASSERT(status, "Failed to initialize Glad!");

        DEBUG_CORE_INFO("> OpenGL Info:");
        //DEBUG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        //DEBUG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        //DEBUG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glClearDepth(1.0f);
        //glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_ALWAYS);  // questo per il 2d        
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(window);
    }
}