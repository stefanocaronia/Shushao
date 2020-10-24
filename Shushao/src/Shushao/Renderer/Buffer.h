#pragma once

namespace Shushao {

    class Buffer
    {
    public:
        virtual ~Buffer() {}
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;  
    };
}