#include "sepch.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexBuffer.h"

namespace Shushao {

    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t count)
    {
        switch (Renderer::GetApiType()) {
            case RendererAPI::Type::OpenGL:
                return new OpenGLVertexBuffer(vertices, count);
            case RendererAPI::Type::None:
                SE_CORE_ASSERT(false, "Renderer API 'None' not supported");
                return nullptr;
        }

        SE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}