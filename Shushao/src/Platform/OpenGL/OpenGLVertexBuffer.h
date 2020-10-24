#pragma once

#include "Shushao/Renderer/VertexBuffer.h"

namespace Shushao {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);

        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetRendererId() const final { return rendererId; }

        virtual void SetLayout(const BufferLayout& _layout) override { layout = _layout; }
        virtual const BufferLayout& GetLayout() const override { return layout; }

        virtual uint32_t GetSize() const { return size; }

    private:
        uint32_t rendererId;
        uint32_t size;
        BufferLayout layout;
    };
}