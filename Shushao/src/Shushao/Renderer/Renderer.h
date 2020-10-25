#pragma once

#include "RenderCommand.h"

namespace Shushao {

    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();

        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RendererAPI::Type GetApiType() { return RendererAPI::GetType(); }
    };
}