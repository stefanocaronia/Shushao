#pragma once

#include "VertexArray.h"

namespace Shushao {

    class RendererAPI
    {
    public:
        enum class Type
        {
            None = 0,
            OpenGL = 1
        };

        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

        inline static Type GetType() { return type; }

    private:
        static Type type;
    };

}

