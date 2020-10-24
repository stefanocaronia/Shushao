#pragma once

#include "Buffer.h"
#include "BufferLayout.h"

namespace Shushao {

    class VertexBuffer : public Buffer
    {
    public:
        virtual ~VertexBuffer() {}
        static VertexBuffer* Create(float* vertices, uint32_t size);

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;
    };
}