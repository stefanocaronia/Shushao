#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Shushao {

    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(VertexBuffer* vertexBuffer) = 0;
        virtual void SetIndexBuffer(IndexBuffer* indexBuffer) = 0;

        virtual std::vector<VertexBuffer*> GetVertexBuffers() const = 0;
        virtual IndexBuffer* GetIndexBuffer() const = 0;

        static VertexArray* Create();
    
    };
}

