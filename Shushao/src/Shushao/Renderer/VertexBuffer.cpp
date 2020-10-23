#include "sepch.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Shushao {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t count)
    {
        switch (Renderer::GetAPI()) {
            case RendererAPI::OpenGL:
                return new OpenGLVertexBuffer(vertices, count);
            case RendererAPI::None:
                SE_CORE_ASSERT(false, "Renderer API 'None' not supported");
                return nullptr;
        }

        SE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}