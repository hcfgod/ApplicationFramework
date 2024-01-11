#pragma once
#include <string>
#include <GLM/ext/matrix_float4x4.hpp>

namespace Visionary
{
    class Shader 
    {
    public:
        Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        unsigned int CompileShader(unsigned int type, const std::string& source);
        void CheckShaderError(unsigned int shader, unsigned int type);

        // Uniform setters
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    private:
        unsigned int m_RendererID;
    };
}