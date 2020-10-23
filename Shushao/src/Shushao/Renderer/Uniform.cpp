#include "sepch.h"

#include <glad/glad.h>

#include "Uniform.h"

namespace Shushao {

    void Uniform::SetFloat(float& value)
    {
        glUniform1f(location, value);
    }

    void Uniform::SetInteger(int& value)
    {
        glUniform1i(location, value);
    }

    void Uniform::SetTextureIndex(int& value)
    {
        glUniform1i(location, (GLint)value);
        texture = value;
    }

    void Uniform::SetMatrix(float* value)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }

    void Uniform::SetVector(glm::vec4& value)
    {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void Uniform::SetVector(glm::vec3& value)
    {
        glUniform3f(location, value.x, value.y, value.z);
    }

    void Uniform::SetVector(glm::vec2& value)
    {
        glUniform2f(location, value.x, value.y);
    }

    void Uniform::SetColor(Color& value)
    {
        glUniform4f(location, value.r, value.g, value.b, value.a);
    }

    //void Uniform::SetLight(UniformLight& value)
    //{
    //    glUniform3f(location, value.position[0], value.position[1], value.position[2]);
    //    glUniform3f(location, value.direction[0], value.direction[1], value.direction[2]);
    //    glUniform3f(location, value.ambient[0], value.ambient[1], value.ambient[2]);
    //    glUniform3f(location, value.diffuse[0], value.diffuse[1], value.diffuse[2]);
    //    glUniform3f(location, value.specular[0], value.specular[1], value.specular[2]);
    //    glUniform1f(location, value.linear);
    //    glUniform1f(location, value.quadratic);
    //    glUniform1f(location, value.cutoff);
    //}
}