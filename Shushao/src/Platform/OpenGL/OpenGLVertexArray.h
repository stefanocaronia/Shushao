#pragma once

#include "Shushao/Renderer/VertexArray.h"

namespace Shushao {
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();

        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        inline virtual uint32_t GetRendererId() const final { return rendererId; }
        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) override;
        virtual void SetIndexBuffer(IndexBuffer* indexBuffer) override;

        virtual std::vector<VertexBuffer*> GetVertexBuffers() const { return vertexBuffers; };
        virtual IndexBuffer* GetIndexBuffer() const { return indexBuffer; };

    private:

        uint32_t rendererId;
        std::vector<VertexBuffer*> vertexBuffers;
        IndexBuffer* indexBuffer;
    };
}

