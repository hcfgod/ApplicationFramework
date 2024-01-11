#pragma once
#include "../UIElement.h"

namespace Visionary 
{
    class Button : public UIElement 
    {
    public:
        // Constructor to initialize the button with an ID and other properties
        Button(const std::string& id, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

        // Draw the button
        void Draw() const override;

        // Update the button state (e.g., check if clicked)
        void Update() override;

        // Set the color that the button should have when hovered over
        void SetHoverColor(const glm::vec4& hoverColor) 
        {
            m_HoverColor = hoverColor; 
        }

        // Method that is called when the button is clicked
        void OnClick();

        bool Clicked();

    private:
        glm::vec4 m_Color;       // Normal color of the button
        glm::vec4 m_HoverColor;  // Color of the button when the mouse hovers over it
        bool m_IsMouseOver;      // Flag to check if mouse is over the button
        bool m_Clicked = false;
    };

}