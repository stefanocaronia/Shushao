#pragma once

#include "Shushao/Renderer/RenderContext.h"

struct GLFWwindow;

namespace Shushao {

    class OpenGLContext : public RenderContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* window;
    };

}