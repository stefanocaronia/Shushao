#pragma once

#include "Shushao/Color.h"

namespace Shushao {

    class Uniform
    {
    public:
        enum class Type
        {
            FLOAT,
            INTEGER,
            MATRIX,
            VECTOR,
            TEXTURE,
            COLOR,
            LIGHT
        };

        Uniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_, bool locked_ = false) :
            name(name_), var(var_), type(type_), location(location_), locked(locked_)
        {}

        std::string name;
        std::string var;
        Uniform::Type type;
        unsigned int location = 0;
        bool locked = false;

        // values
        unsigned int texture = 0;

        void SetFloat(float&);
        void SetInteger(int&);
        void SetTextureIndex(int&);
        void SetMatrix(float*);
        void SetVector(glm::vec2&);
        void SetVector(glm::vec3&);
        void SetVector(glm::vec4&);
        void SetColor(Color&);
        //void SetLight(UniformLight&);
    };

}