#include <Shushao.h>

using namespace Shushao;

class TestLayer : public Shushao::Layer
{
public:
    std::shared_ptr<VertexArray> triangleVAO;
    std::shared_ptr<VertexArray> squareVAO;
    std::shared_ptr<Shader> shader;

    Camera* camera = new OrthographicCamera();
    Entity* triangle = new Entity();
    Entity* square = new Entity();
    Node* root = new Node();

    TestLayer() : Shushao::Layer("Layer di test") {

        root->SetRoot(true);
        root->AddChild(triangle);
        root->AddChild(square);
    
        triangle->GetTransform()->SetPosition({ 4.3f, 0.6f, 0.1f });

        float positions[3 * 3] = {
           -0.5f, -0.5f, 0.0f, // 0
            0.5f, -0.5f, 0.0f, // 1
            0.0f,  0.5f, 0.0f  // 2
        };

        unsigned int indices[3] = {
            0, 1, 2
        };

        float squarePositions[3 * 4] = {
            -0.7f, -0.7f, 0.0f, // 0
             0.7f, -0.7f, 0.0f, // 1
             0.7f,  0.7f, 0.0f, // 2
            -0.7f,  0.7f, 0.0f // 3
        };

        unsigned int squareIndices[6] = {
            0, 1, 2,
            2, 3, 0
        };

        std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 vertex_coord;
            uniform mat4 MVP;

			void main()
			{
                gl_Position = MVP * vec4(vertex_coord, 1.0);
                gl_Position = vec4(vertex_coord, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
            uniform vec4 render_color;

			void main()
			{
                color = vec4(render_color);
			}
		)";
                
        triangleVAO.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> triangleVBO;
        triangleVBO.reset(VertexBuffer::Create(positions, sizeof(positions)));
        triangleVBO->SetLayout({
                { ShaderDataType::Float3, "vertex_coord" }
            });

        std::shared_ptr<IndexBuffer> triangleIBO;
        triangleIBO.reset(IndexBuffer::Create(indices, 3));

        triangleVAO->AddVertexBuffer(triangleVBO);
        triangleVAO->SetIndexBuffer(triangleIBO);

        squareVAO.reset(VertexArray::Create());

        std::shared_ptr<VertexBuffer> squareVBO;
        squareVBO.reset(VertexBuffer::Create(squarePositions, sizeof(squarePositions)));
        squareVBO->SetLayout({
                { ShaderDataType::Float3, "vertex_coord" }
            });

        std::shared_ptr<IndexBuffer> squareIBO;
        squareIBO.reset(IndexBuffer::Create(squareIndices, 6));

        squareVAO->AddVertexBuffer(squareVBO);
        squareVAO->SetIndexBuffer(squareIBO);

        shader.reset(new Shader());
        shader->LoadFromString(vertexSrc, fragmentSrc);
        shader->AddShaderUniform("render_color", Uniform::Type::COLOR);
        shader->Init();   

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });

        square->GetTransform()->Awake();
        triangle->GetTransform()->Awake();
    }

    void OnUpdate() override
    {
        if (Input::IsKeyPressed(SE_KEY_A)) {
            DEBUG_INFO("Hai premuto A!");
        }

        Renderer::BeginScene();
        {
            glm::mat4 VP = camera->GetProjectionMatrix() * camera->GetViewMatrix();
            glm::mat4 MVP;

            square->GetTransform()->Update();
            triangle->GetTransform()->Update();

            shader->Bind();
            MVP = VP * square->GetTransform()->GetModelMatrix();
            shader->SetMVP(&MVP[0][0]);
            shader->SetColor("render_color", color::green);
            Renderer::Submit(squareVAO);

            MVP = VP * triangle->GetTransform()->GetModelMatrix();
            shader->SetMVP(&MVP[0][0]);
            shader->SetColor("render_color", color::magenta);
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
