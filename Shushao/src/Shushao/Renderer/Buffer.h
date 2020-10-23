#pragma once

namespace Shushao {

    class Buffer
    {
    public:
        const uint32_t& Count = count;

        virtual ~Buffer() {}
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

    protected:
        uint32_t count = 0;
    };

}