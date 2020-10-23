#pragma once

#include "Shushao/Renderer/IndexBuffer.h"

namespace Shushao {

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:

        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
        const uint32_t& RendererId = rendererId;

        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

    private:
        uint32_t rendererId;
    };
}