#pragma once

#include "core.h"
#include "debug.h"

namespace se {

static void GLFWErrorCallback(int error, const char* description)
{
    DEBUG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

static void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line)
{
    bool errorFound = false;
    while (GLenum error = glGetError()) {
        std::string msg = "";
        switch (error) {
            case GL_INVALID_ENUM: msg = "Argument out of range"; break;
            case GL_INVALID_VALUE: msg = "Numeric argument out of range"; break;
            case GL_INVALID_OPERATION: msg = "Operation illegal in current state"; break;
            case GL_STACK_OVERFLOW: msg = "Function would cause a stack overflow"; break;
            case GL_STACK_UNDERFLOW: msg = "Function would cause a stack underflow"; break;
            case GL_OUT_OF_MEMORY: msg = "Not enough memory left to execute function"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: msg = "Attempt to read from or write/render to a framebuffer that is not complete"; break;
            case GL_CONTEXT_LOST: msg = "OpenGL context has been lostt"; break;
        }
        std::stringstream stream;
        stream << "0x" << error;

        DEBUG_CORE_ERROR("OpenGL Error {0} ({1}) executing {2}", stream.str(), msg, function);
        DEBUG_CORE_ERROR("OpenGL Error location: {1}:{2}", function, file, line);
        return false;
    }
    return true;
}

#define GL_CALL(x) GLClearError();\
    x;\
    SE_CORE_ASSERT(GLLogCall(#x, __FILE__, __LINE__), "OpenGL Errors") 

}
