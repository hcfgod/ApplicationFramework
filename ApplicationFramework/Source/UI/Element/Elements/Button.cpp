#include "Button.h"
#include "UI/UIElementsManager.h"
#include "Event System/Event/Events/OnButtonClickEvent.h"
#include "Event System/EventManager.h"

namespace Visionary
{
    Button::Button(const std::string& id, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        m_Position = position;
        m_Size = size;
        m_Color = color;
        SetIdentifier(id);
        SetHoverColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        UIElementsManager::GetInstance().AddUIElement(this);
    }

    void Button::Draw() const 
    {
        Renderer2D::DrawQuad(m_Position, m_Size, m_IsMouseOver ? m_HoverColor : m_Color);
    }

    void Button::Update() 
    {  
        m_IsMouseOver = IsMouseOver();
    }

    void Button::OnClick() 
    {
        m_Clicked = true;
        auto event = std::make_shared<OnButtonClickEvent>(GetIdentifier());
        EventManager::Get().DispatchEvent(event);
    }

    bool Button::Clicked()
    {
        if (m_Clicked)
        {
            m_Clicked = false;
            return true;
        }

        return false;
    }
}