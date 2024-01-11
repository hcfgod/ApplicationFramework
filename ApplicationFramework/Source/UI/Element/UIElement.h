#pragma once
#include <string>
#include <iostream>
#include <GLM/ext/vector_float2.hpp>
#include <GLM/ext/vector_float4.hpp>
#include "Rendering/Renderer/Renderer2D.h"
#include "Input/InputManager.h"


namespace Visionary
{
    class UIElement 
    {
    public:
        virtual ~UIElement() = default;

        virtual void Draw() const = 0;
        virtual void Update() = 0;
        virtual void OnClick() = 0;
        // Set and get the identifier
        void SetIdentifier(const std::string& id) { identifier = id; }
        const std::string& GetIdentifier() const { return identifier; }

        void SetZOrder(int zOrder) { m_ZOrder = zOrder; }
        int GetZOrder() const { return m_ZOrder; }

        void SetPosition(const glm::vec2& position) { m_Position = position; }
        const glm::vec2& GetPosition() const { return m_Position; }

        void SetSize(const glm::vec2& size) { m_Size = size; }
        const glm::vec2& GetSize() const { return m_Size; }

        bool Intersects(const glm::vec2& point) const
        {
            glm::vec2 topLeft = m_Position - m_Size * 0.5f;
            glm::vec2 bottomRight = m_Position + m_Size * 0.5f;

            return point.x >= topLeft.x && point.x <= bottomRight.x &&
                point.y >= topLeft.y && point.y <= bottomRight.y;
        }

        // New method to set the mouse-over state
        void SetMouseOver(bool mouseOver) { m_IsMouseOver = mouseOver; }
        bool IsMouseOver() const { return m_IsMouseOver; }

        void SetVisible(bool visible) { m_IsVisible = visible; }
        bool IsVisible() const { return m_IsVisible; }

    protected:
        std::string identifier;  // Unique identifier for the UI element
        int m_ZOrder = 0;
        glm::vec2 m_Position = glm::vec2(0, 0);
        glm::vec2 m_Size = glm::vec2(0, 0);
        bool m_IsVisible = true;
        bool m_IsMouseOver = false;
    };
}