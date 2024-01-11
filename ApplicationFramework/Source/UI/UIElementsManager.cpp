#include "UIElementsManager.h"
#include <algorithm>

namespace Visionary
{
	void UIElementsManager::AddUIElement(UIElement* element) 
	{
		// Ensure the element is not nullptr and doesn't already exist in the list
		if (element && std::find(uiElements.begin(), uiElements.end(), element) == uiElements.end()) 
		{
			uiElements.push_back(element);
		}
	}

	void UIElementsManager::RemoveUIElement(const std::string& id) 
	{
		// Find the element with the given ID and remove it from the list
		auto it = std::find_if(uiElements.begin(), uiElements.end(), [&id](const UIElement* element) 
		{
			return element->GetIdentifier() == id;
		});

		if (it != uiElements.end()) 
		{
			// Optionally, we could also deallocate memory if we are taking ownership
			// delete *it;
			uiElements.erase(it);
		}
	}

	void UIElementsManager::HandleMouseInput(const glm::vec2& mousePosition, MouseButton button)
	{
		for (auto it = uiElements.rbegin(); it != uiElements.rend(); ++it)
		{
			UIElement* element = *it;

			if (element->IsVisible() && element->Intersects(mousePosition))
			{
				element->OnClick();
				break; // Ensures only the topmost clicked element is handled
			}
		}
	}

	UIElement* UIElementsManager::GetTopmostElementAtPoint(const glm::vec2& point) 
	{
		for (auto it = uiElements.rbegin(); it != uiElements.rend(); ++it) 
		{
			UIElement* element = *it;
			if (element->IsVisible() && element->Intersects(point)) 
			{
				return element;
			}
		}
		return nullptr;
	}

	UIElement* UIElementsManager::GetTopmostMouseOverElement()
	{
		glm::vec2 mousePos = InputManager::GetMousePosition();
		for (auto it = uiElements.rbegin(); it != uiElements.rend(); ++it)
		{
			UIElement* element = *it;
			if (element->IsVisible() && element->Intersects(mousePos))
			{
				return element;
			}
		}
		return nullptr;
	}

	void UIElementsManager::SortElements()
	{
		std::sort(uiElements.begin(), uiElements.end(), [](const UIElement* a, const UIElement* b) 
	    {
			return a->GetZOrder() < b->GetZOrder();
		});
	}

	void UIElementsManager::UpdateElements()
	{
		if (InputManager::IsMouseButtonPressed(MouseButton::LeftMouse))
		{
			glm::vec2 mousePos = InputManager::GetMousePosition();
			UIElementsManager::GetInstance().HandleMouseInput(mousePos, MouseButton::LeftMouse);
		}

		UIElement* topElement = UIElementsManager::GetInstance().GetTopmostMouseOverElement();
		for (UIElement* element : UIElementsManager::GetInstance().GetElements())
		{
			// Reset mouse over state for all elements
			element->SetMouseOver(false);

			// Set mouse over state for the topmost element
			if (element == topElement)
			{
				element->SetMouseOver(true);
			}

			// Continue with other update logic...
			element->Update();
		}

		for (const auto& element : uiElements)
		{
			element->Update();
		}
	}

	void UIElementsManager::DrawElements()
	{
		for (const auto& element : uiElements) 
		{
			element->Draw();
		}
	}

	std::vector<UIElement*> UIElementsManager::GetElements()
	{
		return uiElements;
	}
}