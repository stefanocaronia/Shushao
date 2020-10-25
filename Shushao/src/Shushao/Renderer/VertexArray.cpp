#include "sepch.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Shushao {

    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetApiType()) {
            case RendererAPI::Type::OpenGL:
                return new OpenGLVertexArray();
            case RendererAPI::Type::None:
                SE_CORE_ASSERT(false, "Renderer API 'None' not supported");
                return nullptr;
        }

        SE_CORE_ASSERT(false, "Unknown Renderer API");
        return nullptr;
    }
}
