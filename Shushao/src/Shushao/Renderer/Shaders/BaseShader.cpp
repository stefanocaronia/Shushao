#include "sepch.h"

#include "BaseShader.h"
#include "Shushao/Resources.h"

namespace Shushao {

    BaseShader::BaseShader()
    {
        vertexShaderCode = Resources::GetEmbeddedText(BASESHADER_VERT, LIB_SHUSHAO);
        fragmentShaderCode = Resources::GetEmbeddedText(BASESHADER_FRAG, LIB_SHUSHAO);
        Init();
    }

    void BaseShader::onAwake()
    {
        AddShaderUniform("M", Uniform::Type::MATRIX);
        AddShaderUniform("viewport", Uniform::Type::VECTOR);
        AddShaderUniform("enabled_viewport", Uniform::Type::INTEGER);
    }
}  // namespace se
