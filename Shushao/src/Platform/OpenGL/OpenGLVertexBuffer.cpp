#include "sepch.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGL.h"

#include <glad/glad.h>

namespace Shushao {
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t _size) : size(_size)
    {
        glCreateBuffers(1, &rendererId);
        glBindBuffer(GL_ARRAY_BUFFER, rendererId);
        glBufferData(GL_ARRAY_BUFFER, _size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &rendererId);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererId);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

}
