#pragma once

#include "Shushao/Renderer/Shader.h"

namespace Shushao {

    class BaseShader : public Shader
    {
    public:
        BaseShader();
    protected:
        virtual void onAwake() override;
    };

}  // namespace Shushao
