#pragma once

#include "Buffer.h"

namespace Shushao {

    class IndexBuffer : public Buffer
    {
    public:
        virtual ~IndexBuffer() {}
        static IndexBuffer* Create(uint32_t* vertices, uint32_t count);
    };

}