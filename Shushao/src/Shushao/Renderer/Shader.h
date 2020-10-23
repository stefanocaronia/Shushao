#pragma once

#include "Shushao/Color.h"
//#include "Shushao/Light.h"
#include "Shushao/Object.h"
#include "Uniform.h"

namespace Shushao {

    enum ShaderLocation
    {
        LOCATION_POSITION = 1,
        LOCATION_TEXCOORD = 2,
        LOCATION_COLOR = 3,
        LOCATION_NORMAL = 4,
        LOCATION_MVP = 5,
        LOCATION_RENDER_COLOR = 6,
        LOCATION_SIZE = 7
    };

    class Shader : public Object
    {
    public:
        const uint32_t& RendererId = rendererId;
        std::map<std::string, Uniform> uniforms;
        bool inUse = false;

        Shader(std::string fileBasename = "", std::string shaderName = "");
        ~Shader();

        bool Load(std::string);
        void LoadFromString(std::string vsc, std::string fsc, std::string gsc = "");

        virtual void Init() final;
        void Bind();
        void Unbind();
        virtual void Awake() final;
        virtual void Update() final;

        void AddUniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_ = 0);
        void AddUniform(std::string var_, Uniform::Type type_, unsigned int location_ = 0);
        void AddShaderUniform(std::string var_, Uniform::Type type_, unsigned int location_ = 0);
        void AddShaderUniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_ = 0);

        void SetFloat(std::string, float);
        void SetInteger(std::string, int);
        void SetTextureIndex(std::string, int);
        void SetMatrix(std::string, float*);
        void SetVector(std::string, glm::vec2);
        void SetVector(std::string, glm::vec3);
        void SetVector(std::string, glm::vec4);
        void SetColor(std::string, Color);
        //void SetLight(std::string, UniformLight&);

        uint32_t GetTextureIndex(std::string);

        void SetMVP(float*);
        void SetMV(float*);
        void SetVP(float*);
        void SetP(float*);
        void SetV(float*);
        void SetM(float*);
        void SetRenderColor(Color);

        void Enable(std::string var);
        void Disable(std::string var);

    protected:
        virtual void onAwake() {}
        virtual void onUpdate() {}
        virtual void onExit() {}

        std::string vertexShaderCode;
        std::string fragmentShaderCode;
        std::string geometryShaderCode;

    private:
        uint32_t rendererId = 0;
        uint32_t vertexShaderID;
        uint32_t fragmentShaderID;
        uint32_t geometryShaderID;

        bool shaderCompilationLog(const unsigned int&);
        bool programCompilationLog(const unsigned int&);

        bool compile();
        bool link();
        void initUniforms();
    };

}  // Shushao
