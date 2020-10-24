#pragma once

#include "Shushao/Renderer/IndexBuffer.h"

namespace Shushao {

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);

        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetRendererId() const final { return rendererId; }

        virtual uint32_t GetCount() const override { return count; }

    private:
        uint32_t rendererId;
        uint32_t count;
    };
}