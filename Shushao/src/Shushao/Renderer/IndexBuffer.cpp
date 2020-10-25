#include "sepch.h"

#include "Renderer.h"
#include "IndexBuffer.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"

namespace Shushao {

    IndexBuffer* IndexBuffer::Create(uint32_t* vertices, uint32_t count)
    {
        switch (Renderer::GetApiType()) {
            case RendererAPI::Type::OpenGL:
                return new OpenGLIndexBuffer(vertices, count);
            case RendererAPI::Type::None:
                SE_CORE_ASSERT(false, "Renderer API 'None' not supported");
                return nullptr;
        }

        SE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}