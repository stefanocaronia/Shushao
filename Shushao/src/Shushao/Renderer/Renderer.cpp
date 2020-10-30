#include "sepch.h"

#include "Renderer.h"
#include "Shader.h"
#include "Shushao/Core/Transform.h"

namespace Shushao {

    Renderer::Data* Renderer::data = new Renderer::Data;

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Transform>& transform)
    {
        glm::mat4 VP = Renderer::data->camera->GetViewProjectionMatrix();
        glm::mat4 M = transform->GetModelMatrix();

        shader->Bind();
        shader->SetVP(glm::value_ptr(VP));
        shader->SetM(glm::value_ptr(M));

        vertexArray->Bind();

        RenderCommand::DrawIndexed(vertexArray);
    }

}