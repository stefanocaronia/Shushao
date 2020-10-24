#pragma once

#include "Buffer.h"

namespace Shushao {

    class IndexBuffer : public Buffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual uint32_t GetCount() const = 0;

        static IndexBuffer* Create(uint32_t* vertices, uint32_t count);
    };

}