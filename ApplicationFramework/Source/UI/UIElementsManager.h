#pragma once
#include <vector>
#include "Element/UIElement.h"
#include <GLM/ext/vector_float2.hpp>
#include <Input/MouseButton.h>

namespace Visionary
{
	class UIElementsManager
	{
	public:
		UIElementsManager(UIElementsManager const&) = delete;
		void operator=(UIElementsManager const&) = delete;

		static UIElementsManager& GetInstance() 
		{
			static UIElementsManager instance;
			return instance;
		}

		void AddUIElement(UIElement* element);
		void RemoveUIElement(const std::string& id);

		void HandleMouseInput(const glm::vec2& mousePosition, MouseButton button);
		UIElement* GetTopmostElementAtPoint(const glm::vec2& point);
		UIElement* GetTopmostMouseOverElement();

		std::vector<UIElement*> GetElements();

		void SortElements();
		void UpdateElements();
		void DrawElements();
	private:
		std::vector<UIElement*> uiElements;

		UIElementsManager() {}
		~UIElementsManager() {}
	};
}