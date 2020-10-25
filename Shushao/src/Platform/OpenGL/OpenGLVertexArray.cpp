#include "sepch.h"

#include <glad/glad.h>
#include "OpenGLVertexArray.h"

namespace Shushao {

    static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
    {
        switch (type) {
            case ShaderDataType::Float:
            case ShaderDataType::Float2:
            case ShaderDataType::Float3:
            case ShaderDataType::Float4:
            case ShaderDataType::Mat3:
            case ShaderDataType::Mat4:
                return GL_FLOAT;
            case ShaderDataType::Int:
            case ShaderDataType::Int2:
            case ShaderDataType::Int3:
            case ShaderDataType::Int4:
                return GL_INT;
            case ShaderDataType::Bool:
                return GL_BOOL;
        }

        SE_CORE_ASSERT(false, "Unknown Shader data type!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &rendererId);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &rendererId);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(rendererId);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(rendererId);
        vertexBuffer->Bind();

        SE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

        uint32_t index = 0;
        for (const auto& element : vertexBuffer->GetLayout()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLType(element.Type),
                element.Normalized ? GL_TRUE : GL_FALSE,
                vertexBuffer->GetLayout().GetStride(),
                (const void*)element.Offset
            );
            index++;
        }

        vertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& _indexBuffer)
    {
        glBindVertexArray(rendererId);
        _indexBuffer->Bind();

        indexBuffer = _indexBuffer;
    }

}