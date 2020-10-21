#pragma once

#include "Shushao/Renderer/GraphicContext.h"

struct GLFWwindow;

namespace Shushao {

    class OpenGLContext : public GraphicContext
    {
    public:
        OpenGLContext(GLFWwindow* window);

        virtual void Initialize() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* window;
    };

}