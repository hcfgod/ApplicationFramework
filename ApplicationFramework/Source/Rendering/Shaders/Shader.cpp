#include "Shader.h"
#include <GLAD/glad.h>
#include <iostream>
#include <GLM/gtc/type_ptr.hpp>

namespace Visionary
{
    Shader::Shader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
    {
        unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSrc);
        unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

        // Create shader program
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);
        glLinkProgram(m_RendererID);

        // Check for linking errors
        CheckShaderError(m_RendererID, GL_LINK_STATUS);

        // Delete shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }


    unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
    {
        unsigned int id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Check for compilation errors
        CheckShaderError(id, GL_COMPILE_STATUS);

        return id;
    }

    void Shader::CheckShaderError(unsigned int shader, unsigned int type) 
    {
        int success;
        char infoLog[1024];

        if (type == GL_COMPILE_STATUS)
        {
            glGetShaderiv(shader, type, &success);
            if (!success) 
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        else if (type == GL_LINK_STATUS) 
        {
            glGetProgramiv(shader, type, &success);
            if (!success) 
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cerr << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
            }
        }
    }

    void Shader::SetUniform1i(const std::string& name, int value)
    {
        glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void Shader::SetUniform1f(const std::string& name, float value)
    {
        glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), value);
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), v0, v1, v2, v3);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}