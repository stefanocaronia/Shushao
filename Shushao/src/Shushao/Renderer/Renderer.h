#pragma once

#include "Shushao/Nodes/Camera.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Shushao {

    class Renderer
    {
    public:

        inline static RendererAPI::Type GetApiType() { return RendererAPI::GetType(); }

        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Transform>& transform);
        static void SetActiveCamera(Camera* _camera) { data->camera = _camera; }

        //static void BeginScene();
        //static void EndScene();

    private:
        struct Data
        {
            Camera* camera;
        };

        static Data* data;
    };
}