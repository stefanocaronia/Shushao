#include <Shushao.h>

using namespace Shushao;

class TestLayer : public Shushao::Layer
{
public:
    std::shared_ptr<VertexArray> triangleVAO;
    std::shared_ptr<VertexArray> squareVAO;
    std::shared_ptr<Shader> shader;

    OrthographicCamera* camera = new OrthographicCamera();
    Entity* triangle = new Entity();
    Entity* square = new Entity();
    Entity* root = new Entity();
    float cameraSpeed = 5.0f;

    TestLayer() : Shushao::Layer("Layer di test")
    {
        root->SetRoot(true);
        root->AddChild(camera);
        root->AddChild(triangle);
        root->AddChild(square);

        camera->SetNearClipPlane(0.05f);
        camera->SetFarClipPlane(100.0f);
        camera->SetOrthographicSize(10.0f);
        //camera->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -3.0f });
        //camera->GetTransform()->SetLocalRotation(Transform::QUATERNION_IDENTITY);

        camera->Print();

        //triangle->GetTransform()->SetPosition({ 0.3f, 0.6f, 0.1f });

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
			#version 430 core
			
			layout(location = 0) in vec3 vertex_coord;

            uniform mat4 VP;
            //uniform mat4 M;

			void main()
			{
                gl_Position = VP * vec4(vertex_coord, 1.0);
                //gl_Position = vec4(vertex_coord, 1.0);
			}
		)";

        std::string fragmentSrc = R"(
			#version 430 core
			
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

        Renderer::SetActiveCamera(camera);

        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.4f, 1.0f });

        ImGuiLayer* gui = new ImGuiLayer();
        gui->Begin();


        gui->End();
    }

    void OnUpdate() override
    {
        std::shared_ptr<Transform> cameraTransform = camera->GetTransform();
        glm::vec3 cameraPosition = cameraTransform->GetLocalPosition();
        glm::vec3 cameraRotation = cameraTransform->GetEulerAngles();

        if (Input::IsKeyPressed(SE_KEY_LEFT)) {
            cameraPosition.x -= cameraSpeed * Time::Delta;
            DEBUG_INFO("Camera VP: {0},{1} ", cameraTransform->GetPosition().x, cameraTransform->GetPosition().y);
        }

        else if (Input::IsKeyPressed(SE_KEY_RIGHT)) {
            cameraPosition.x += cameraSpeed * Time::Delta;
            DEBUG_INFO("Camera VP: {0},{1} ", cameraTransform->GetPosition().x, cameraTransform->GetPosition().y);
        }

        if (Input::IsKeyPressed(SE_KEY_UP))
            cameraPosition.y += cameraSpeed * Time::Delta;
        else if (Input::IsKeyPressed(SE_KEY_DOWN))
            cameraPosition.y -= cameraSpeed * Time::Delta;

        if (Input::IsKeyPressed(SE_KEY_A))
            cameraRotation.y += cameraSpeed * Time::Delta;

        if (Input::IsKeyPressed(SE_KEY_D)) {
            cameraRotation.y -= cameraSpeed * Time::Delta;
        }

        cameraTransform->SetLocalPosition(cameraPosition);
        cameraTransform->SetLocalRotation(cameraRotation);

        camera->GetTransform()->Update();
        camera->Update();
        square->GetTransform()->Update();
        triangle->GetTransform()->Update();

        shader->Bind();
        shader->SetColor("render_color", color::cyan);
        Renderer::Submit(shader, squareVAO, square->GetTransform());

        shader->SetColor("render_color", color::gray);
        Renderer::Submit(shader, triangleVAO, triangle->GetTransform());
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
