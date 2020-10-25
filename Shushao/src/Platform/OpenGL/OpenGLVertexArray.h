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

        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers; }
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return indexBuffer; }

    private:

        uint32_t rendererId;
        std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
        std::shared_ptr<IndexBuffer> indexBuffer;
    };
}

