#pragma once

#include "Window/Window.h"
#include <Rendering/Camera/OrthographicCamera.h>
#include <UI/UIElementsManager.h>

namespace Visionary
{
	struct ApplicationSettings
	{
		int InitalWindowWidth = 640;;
		int InitalWindowHeight = 480;

		ApplicationSettings()
		{
			InitalWindowWidth = 640;
			InitalWindowHeight = 480;
		}

		ApplicationSettings(int intialWindowWidth, int initialWindowHeight)
		{
			InitalWindowWidth = intialWindowWidth;
			InitalWindowHeight = initialWindowHeight;
		}
	};

	class Application
	{
	public:
		Application(const char* windowTitle, ApplicationSettings applicationSettings);
		~Application();

		void Run();

		Window* GetWindow();

	private:
		Window* m_Window = nullptr;
		float m_AspectRatio = 0;
		OrthographicCamera* m_OrthographicCamera = nullptr;
	};
}