#include "sepch.h"

#include "Shader.h"
//#include "Shushao/Light.h"

#include <glad/glad.h>

namespace Shushao {

    Shader::Shader(std::string fileBasename, std::string shaderName)
    {
        name = (shaderName != "" ? shaderName : fileBasename);

        if (fileBasename != "") {
            if (!Load(fileBasename)) {
                DEBUG_CORE_ERROR("Error Loading Shader: {0}", name);
                return;
            }

            Init();
        }
    }

    void Shader::Init()
    {
        compile();
        link();
        initUniforms();
    }

    Shader::~Shader()
    {
        DEBUG_CORE_TRACE("Destructor di Shader: {0}", name);
        uniforms.clear();
        Unbind();

        if (vertexShaderID > 0) glDeleteShader(vertexShaderID);
        if (fragmentShaderID > 0) glDeleteShader(fragmentShaderID);
        if (geometryShaderID > 0) glDeleteShader(geometryShaderID);
        if (rendererId > 0) glDeleteProgram(rendererId);
    }

    void Shader::LoadFromString(std::string vsc, std::string fsc, std::string gsc)
    {
        vertexShaderCode = vsc;
        fragmentShaderCode = fsc;
        geometryShaderCode = gsc;
    }

    bool Shader::Load(std::string shaderfile)
    {
        std::string vert = shaderfile + ".vert";
        std::string frag = shaderfile + ".frag";
        std::string geom = shaderfile + ".geom";

        // Read the Vertex Shader code from the file
        std::ifstream VertexShaderStream(vert.c_str(), std::ifstream::in);
        if (VertexShaderStream.is_open()) {
            std::string Line = "";
            while (std::getline(VertexShaderStream, Line))
                vertexShaderCode += "\n" + Line;
            VertexShaderStream.close();
        } else {
            DEBUG_CORE_ERROR("Impossibile aprire il file {0}", vert);
        }

        // Read the Fragment Shader code from the file
        std::ifstream FragmentShaderStream(frag.c_str(), std::ifstream::in);
        if (FragmentShaderStream.is_open()) {
            std::string Line = "";
            while (std::getline(FragmentShaderStream, Line))
                fragmentShaderCode += "\n" + Line;
            FragmentShaderStream.close();
        } else {
            //Debug::Log(ERROR, SOURCE) << "Impossibile aprire il file " << frag << std::endl;
            DEBUG_CORE_ERROR("Impossibile aprire il file {0}", frag);
        }

        // Read the Geometry Shader code from the file
        std::ifstream GeometryShaderStream(geom.c_str(), std::ifstream::in);
        if (GeometryShaderStream.is_open()) {
            std::string Line = "";
            while (std::getline(GeometryShaderStream, Line))
                geometryShaderCode += "\n" + Line;
            GeometryShaderStream.close();
        } else {
            //Debug::Log(ERROR, SOURCE) << "Impossibile aprire il file " << frag << std::endl;
            DEBUG_CORE_ERROR("Impossibile aprire il file {0}", geom);
        }

        return true;
    }

    void Shader::Awake()
    {
        Bind();
        onAwake();     
        Unbind();
    }

    void Shader::Update()
    {
        onUpdate();
    }

    void Shader::Bind()
    {
        SE_ASSERT(rendererId > 0, "Render ID doesn't exists for Shader {0}", name);
        glUseProgram(rendererId);
        inUse = true;
    }

    void Shader::Unbind()
    {
        SE_ASSERT(rendererId > 0, "Render ID doesn't exists for Shader {0}", name);
        glUseProgram(0);
        inUse = false;
    }

    void Shader::initUniforms()
    {
        SE_ASSERT(rendererId > 0, "Render ID doesn't exists for Shader {0}", name);

        // base uniforms
        AddShaderUniform("Model View Projection", "MVP", Uniform::Type::MATRIX, ShaderLocation::LOCATION_MVP);
        AddShaderUniform("Render Color", "render_color", Uniform::Type::COLOR, ShaderLocation::LOCATION_RENDER_COLOR);

        for (auto& it : uniforms) {
            if (!it.second.location) {
                it.second.location = glGetUniformLocation(rendererId, (const GLchar*)it.first.c_str());
            }
        }
    }

    #pragma region compilation

    bool Shader::compile()
    {
        if (fragmentShaderCode != "") {
            vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            char const* VertexSourcePointer = vertexShaderCode.c_str();
            glShaderSource(vertexShaderID, 1, &VertexSourcePointer, NULL);
            glCompileShader(vertexShaderID);
            if (!shaderCompilationLog(vertexShaderID))
                return false;
        }

        if (fragmentShaderCode != "") {
            fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            char const* FragmentSourcePointer = fragmentShaderCode.c_str();
            glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer, NULL);
            glCompileShader(fragmentShaderID);
            if (!shaderCompilationLog(fragmentShaderID))
                return false;
        }

        if (geometryShaderCode != "") {
            geometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);
            char const* GeometrySourcePointer = geometryShaderCode.c_str();
            glShaderSource(geometryShaderID, 1, &GeometrySourcePointer, NULL);
            glCompileShader(geometryShaderID);
            if (!shaderCompilationLog(geometryShaderID))
                return false;
        }

        return true;
    }

    bool Shader::link()
    {
        rendererId = glCreateProgram();
        if (vertexShaderID > 0) glAttachShader(rendererId, vertexShaderID);
        if (fragmentShaderID > 0) glAttachShader(rendererId, fragmentShaderID);
        if (geometryShaderID > 0) glAttachShader(rendererId, geometryShaderID);
        glLinkProgram(rendererId);

        if (!programCompilationLog(rendererId))
            return false;

        if (vertexShaderID > 0) glDeleteShader(vertexShaderID);
        if (fragmentShaderID > 0) glDeleteShader(fragmentShaderID);
        if (geometryShaderID > 0) glDeleteShader(geometryShaderID);

        return true;
    }
     
    bool Shader::shaderCompilationLog(const unsigned int& shader)
    {
        GLint status;
        std::string script;
        if (shader == vertexShaderID)
            script = "Vertex";
        else if (shader == fragmentShaderID)
            script = "Fragment";
        else if (shader == geometryShaderID)
            script = "Geometry";

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            DEBUG_CORE_ERROR("Shader {0} script {1} compilation failed:\n {2}", name, script, infoLog);
            return false;
        }
        return true;
    }

    bool Shader::programCompilationLog(const unsigned int& program)
    {
        GLint status;
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint infoLogLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
            DEBUG_CORE_ERROR("Shader {0} Program compilation failed:\n {1}", name, infoLog);
            delete[] infoLog;
            return false;
        }
        return true;
    }

    #pragma endregion

    #pragma region uniform setter

    void Shader::SetFloat(std::string var_, float value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetFloat(value);
        } else {
            glUniform1f(glGetUniformLocation(rendererId, var_.c_str()), (GLfloat)value);
        }
    }

    void Shader::SetInteger(std::string var_, int value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetInteger(value);
        } else {
            glUniform1i(glGetUniformLocation(rendererId, var_.c_str()), (GLint)value);
        }
    }

    void Shader::SetTextureIndex(std::string var_, int value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetTextureIndex(value);
        } else {
            glUniform1i(glGetUniformLocation(rendererId, var_.c_str()), (GLint)value);
        }
    }

    //void Shader::SetLight(std::string var_, UniformLight& value)
    //{
    //    glUniform3f(glGetUniformLocation(programID, (var_ + ".position").c_str()), value.position[0], value.position[1], value.position[2]);
    //    glUniform3f(glGetUniformLocation(programID, (var_ + ".direction").c_str()), value.direction[0], value.direction[1], value.direction[2]);
    //    glUniform3f(glGetUniformLocation(programID, (var_ + ".ambient").c_str()), value.ambient[0], value.ambient[1], value.ambient[2]);
    //    glUniform3f(glGetUniformLocation(programID, (var_ + ".diffuse").c_str()), value.diffuse[0], value.diffuse[1], value.diffuse[2]);
    //    glUniform3f(glGetUniformLocation(programID, (var_ + ".specular").c_str()), value.specular[0], value.specular[1], value.specular[2]);
    //    glUniform1f(glGetUniformLocation(programID, (var_ + ".linear").c_str()), value.linear);
    //    glUniform1f(glGetUniformLocation(programID, (var_ + ".quadratic").c_str()), value.quadratic);
    //    glUniform1f(glGetUniformLocation(programID, (var_ + ".cutoff").c_str()), value.cutoff);
    //}

    void Shader::SetMatrix(std::string var_, float* value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetMatrix(value);
        } else {
            glUniformMatrix4fv(glGetUniformLocation(rendererId, var_.c_str()), 1, GL_FALSE, (GLfloat*)value);
        }
    }

    void Shader::SetVector(std::string var_, glm::vec3 value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetVector(value);
        } else {
            glUniform3f(glGetUniformLocation(rendererId, var_.c_str()), value.x, value.y, value.z);
        }
    }

    void Shader::SetVector(std::string var_, glm::vec4 value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetVector(value);
        } else {
            glUniform4f(glGetUniformLocation(rendererId, var_.c_str()), value.x, value.y, value.z, value.w);
        }
    }

    void Shader::SetVector(std::string var_, glm::vec2 value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetVector(value);
        } else {
            glUniform2f(glGetUniformLocation(rendererId, var_.c_str()), value.x, value.y);
        }
    }

    void Shader::SetColor(std::string var_, Color value)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) {
            it->second.SetColor(value);
        } else {
            glUniform4f(glGetUniformLocation(rendererId, var_.c_str()), value.r, value.g, value.b, value.a);
        }
    }

    GLenum Shader::GetTextureIndex(std::string var_)
    {
        auto it = uniforms.find(var_);
        if (it != uniforms.end()) return it->second.texture;
        return 0;
    }

    void Shader::SetMVP(float* value)
    {
        SetMatrix("MVP", value);
    }

    void Shader::SetMV(float* value)
    {
        SetMatrix("MV", value);
    }

    void Shader::SetVP(float* value)
    {
        SetMatrix("VP", value);
    }

    void Shader::SetM(float* value)
    {
        SetMatrix("M", value);
    }

    void Shader::SetP(float* value)
    {
        SetMatrix("P", value);
    }

    void Shader::SetV(float* value)
    {
        SetMatrix("V", value);
    }

    void Shader::SetRenderColor(Color value)
    {
        SetColor("render_color", value);
    }

    void Shader::Enable(std::string var_)
    {
        SetInteger("enabled_" + var_, 1);
    }

    void Shader::Disable(std::string var_)
    {
        SetInteger("enabled_" + var_, 0);
    }

    void Shader::AddUniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_)
    {
        uniforms.insert(std::pair<std::string, Uniform>(var_, { name_, var_, type_, location_, false }));
    }

    void Shader::AddUniform(std::string var_, Uniform::Type type_, unsigned int location_)
    {
        uniforms.insert(std::pair<std::string, Uniform>(var_, { var_, var_, type_, location_, false }));
    }

    void Shader::AddShaderUniform(std::string var_, Uniform::Type type_, unsigned int location_)
    {
        uniforms.insert(std::pair<std::string, Uniform>(var_, { var_, var_, type_, location_, true }));
    }

    void Shader::AddShaderUniform(std::string name_, std::string var_, Uniform::Type type_, unsigned int location_)
    {
        uniforms.insert(std::pair<std::string, Uniform>(var_, { name_, var_, type_, location_, true }));
    }

    #pragma endregion

}  // Shushao
