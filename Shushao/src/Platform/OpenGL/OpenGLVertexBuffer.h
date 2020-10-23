#pragma once

#include "Shushao/Renderer/VertexBuffer.h"

namespace Shushao {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        const uint32_t& RendererId = rendererId;

        OpenGLVertexBuffer(float* vertices, uint32_t count);

        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t rendererId;
    };
}