#include "sepch.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Shushao/Window.h"
#include "OpenGLContext.h"

namespace Shushao {

    OpenGLContext::OpenGLContext(GLFWwindow* _window) : window(_window)
    {
        SE_CORE_ASSERT(_window, "Window is null!")
    }

    void OpenGLContext::Initialize()
    {
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SE_CORE_ASSERT(status, "Failed to initialize Glad!");

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);  // questo per il 2d        
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(window);
    }
}