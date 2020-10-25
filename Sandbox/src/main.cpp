#include <Shushao.h>

using namespace Shushao;

class TestLayer : public Shushao::Layer
{
public:
    std::shared_ptr<VertexArray> triangleVAO;
    std::shared_ptr<VertexArray> squareVAO;
    std::shared_ptr<Shader> shader;

    TestLayer() : Shushao::Layer("Layer di test") {
    
        float positions[3 * 3] = {
                -0.5f, -0.5f, 0.0f, // 0
                 0.5f, -0.5f, 0.0f, // 1
                 0.0f,  0.5f, 0.0f  // 2
        };

        unsigned int indices[3] = {
            0, 1, 2
        };

        float squarePositions[7 * 4] = {
            -0.7f, -0.7f, 0.0f,      0.4f, 0.8f, 0.2f, 1.0f,// 0
             0.7f, -0.7f, 0.0f,      0.4f, 0.8f, 0.2f, 1.0f,// 1
             0.7f,  0.7f, 0.0f,      0.4f, 0.8f, 0.2f, 1.0f,// 2
            -0.7f,  0.7f, 0.0f,      0.4f, 0.8f, 0.2f, 1.0f // 3
        };

        unsigned int squareIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
                if (v_Color[0] > 0.0) {
                    color = vec4(v_Color);
                } else {
				    color = vec4(v_Position * 0.5 +0.5, 1.0);
                }
			}
		)";
                
        triangleVAO.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> triangleVBO;
        triangleVBO.reset(VertexBuffer::Create(positions, sizeof(positions)));
        triangleVBO->SetLayout({
                { ShaderDataType::Float3, "a_Position" }
            });

        std::shared_ptr<IndexBuffer> triangleIBO;
        triangleIBO.reset(IndexBuffer::Create(indices, 3));

        triangleVAO->AddVertexBuffer(triangleVBO);
        triangleVAO->SetIndexBuffer(triangleIBO);

        squareVAO.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> squareVBO;
        squareVBO.reset(VertexBuffer::Create(squarePositions, sizeof(squarePositions)));
        squareVBO->SetLayout({
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color" }
            });

        std::shared_ptr<IndexBuffer> squareIBO;
        squareIBO.reset(IndexBuffer::Create(squareIndices, 6));

        squareVAO->AddVertexBuffer(squareVBO);
        squareVAO->SetIndexBuffer(squareIBO);

        shader.reset(new Shader());
        shader->LoadFromString(vertexSrc, fragmentSrc);
        shader->Init();

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    }

    void OnUpdate() override
    {
        if (Input::IsKeyPressed(SE_KEY_A)) {
            DEBUG_INFO("Hai premuto A!");
        }

        Renderer::BeginScene();
        {
            shader->Bind();
            Renderer::Submit(squareVAO);
            Renderer::Submit(triangleVAO);
        }
        Renderer::EndScene();
    }

    void OnEvent(Shushao::Event& event) override
    {
        //DEBUG_INFO("Received event {0} ", event);
        event.Handled = true;
    }
};

class Sandbox : public Shushao::Application
{
public:

    Sandbox()
    {
        PushLayer(new TestLayer());
    }
};

Shushao::Application* Shushao::CreateApplication()
{
    return new Sandbox();
}
