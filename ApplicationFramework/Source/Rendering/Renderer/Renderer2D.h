#pragma once

#include "Rendering/Camera/OrthographicCamera.h"
#include "Rendering/Texture.h"

namespace Visionary
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera* camera);
        static void EndScene();

        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawTexturedQuad(const glm::vec2& position, const glm::vec2& size, const Texture& texture, const glm::vec4& tintColor);
    };
}