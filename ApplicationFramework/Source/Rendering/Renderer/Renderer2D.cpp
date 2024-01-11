#include "Renderer2D.h"
#include "../Shaders/Shader.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Visionary
{
    #pragma region ShaderCode

    const std::string vertexShaderSource =
    R"glsl(
    #version 330 core
    layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 aTexCoords;

	uniform mat4 u_Model;
    uniform mat4 u_ViewProjection;

    out vec2 TexCoords;

    void main()
    {
        gl_Position = u_ViewProjection * u_Model * vec4(aPos, 1.0);
        TexCoords = aTexCoords;
    }
	)glsl";

    const std::string fragmentShaderSource =
    R"glsl(
    #version 330 core
    out vec4 FragColor;

    in vec2 TexCoords;

    uniform int u_UseTexture;
    uniform vec4 u_Color;
    uniform sampler2D u_Texture;

    void main()
    {
        vec4 texColor = texture(u_Texture, TexCoords);
        if (u_UseTexture == 1) 
        {
            FragColor = texColor * u_Color;
        }
        else 
        {
            FragColor = u_Color;
        }
    }
    )glsl";

    #pragma endregion

    Shader* m_Shader;

    VertexArray* m_QuadVertexArray;
    VertexBuffer* m_QuadVertexBuffer;
    IndexBuffer* m_QuadIndexBuffer;

    void Renderer2D::Init()
    {
        float quadVertices[] = 
        {
            // Position         // Texture Coords
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // Bottom left
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // Bottom right
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // Top right
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f  // Top left
        };
        unsigned int quadIndices[] =
        {
            0, 1, 2,  // First Triangle
            2, 3, 0   // Second Triangle
        };

        m_QuadVertexArray = new VertexArray();
        unsigned int quadVerticesSize = sizeof(quadVertices);
        m_QuadVertexBuffer = new VertexBuffer(quadVertices, quadVerticesSize);

        VertexBufferLayout layout;
        layout.Push<float>(3); // 3 floats per vertex
        layout.Push<float>(2); // 2 floats for texture coordinates

        m_QuadVertexArray->AddBuffer(*m_QuadVertexBuffer, layout);

        m_QuadIndexBuffer = new IndexBuffer(quadIndices, 6); // 6 indices for 2 triangles

        // Load shaders
        m_Shader = new Shader(vertexShaderSource, fragmentShaderSource);
    }

    void Renderer2D::Shutdown()
    {
        
    }

    void Renderer2D::BeginScene(const OrthographicCamera* camera) 
    {
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_ViewProjection", camera->GetViewProjectionMatrix());
        m_QuadVertexArray->Bind();
    }

    void Renderer2D::EndScene() 
    {
        m_QuadVertexArray->Unbind();
        m_Shader->Unbind();
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) 
    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        m_Shader->SetUniform1i("u_UseTexture", 0);
        m_Shader->SetUniformMat4f("u_Model", model);
        m_Shader->SetUniform4f("u_Color", color.r, color.g, color.b, color.a);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    void Renderer2D::DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const Texture& texture, const glm::vec4& tintColor)
    {
        texture.Bind();

        // Set up the model matrix as before
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

        m_Shader->SetUniform1i("u_UseTexture", 1); // Indicate to use texture
        m_Shader->SetUniformMat4f("u_Model", model);
        m_Shader->SetUniform4f("u_Color", tintColor.r, tintColor.g, tintColor.b, tintColor.a);

        // Draw the quad
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}