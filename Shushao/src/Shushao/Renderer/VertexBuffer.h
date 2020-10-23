#pragma once

#include "Buffer.h"

namespace Shushao {

    class VertexBuffer : public Buffer
    {
    public:
        virtual ~VertexBuffer() {}
        static VertexBuffer* Create(float* vertices, uint32_t count);
    };
}