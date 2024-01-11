#include "GLAD/glad.h"
#include <iostream>

#include "Application.h"
#include "Event System/EventManager.h"
#include <Event System/Event/Events/WindowResizeEvent.h>
#include <Rendering/Renderer/Renderer2D.h>
#include <UI/Element/Elements/Button.h>
#include <Event System/Event/Events/OnButtonClickEvent.h>

namespace Visionary
{
	Application::Application(const char* windowTitle, ApplicationSettings applicationSettings)
	{
		if (!glfwInit())
			return;

		m_Window = new Window(windowTitle, applicationSettings.InitalWindowWidth, applicationSettings.InitalWindowHeight);
		m_AspectRatio = (float)(m_Window->GetWindowSize().x / m_Window->GetWindowSize().y);

		if (!gladLoadGL())
			return;

		Visionary::InputManager::SetWindow(m_Window->GetGlfwWindow());

		Renderer2D::Init();
		m_OrthographicCamera = new OrthographicCamera(0, m_Window->GetWindowSize().x, 0, m_Window->GetWindowSize().y);

		EventManager::Get().RegisterEvent<WindowResizeEvent>([this](const WindowResizeEvent& e)
		{
				m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
				glViewport(0, 0, e.GetWidth(), e.GetHeight());
				m_OrthographicCamera->SetProjection(0, e.GetWidth(), 0, e.GetHeight());
		}, this);


		EventManager::Get().RegisterEvent<OnButtonClickEvent>([](const OnButtonClickEvent& event)
		{
				if (event.GetButtonId() == "testButton2")
				{
					std::cout << "Button clicked: " << event.GetButtonId() << std::endl;
				}
		},this);
	}

	Application::~Application()
	{
		EventManager::Get().UnregisterEvent<WindowResizeEvent>(this);
		Renderer2D::Shutdown();

		delete m_Window;

		glfwTerminate();
	}

	void Application::Run() 
	{
		Texture testTexture = Texture("logo.png");
		Button myButton("testButton", glm::vec2(200, 170), glm::vec2(100, 50), glm::vec4(0.1f, 0.5f, 0.2f, 1.0f));
		Button myButton2("testButton2", glm::vec2(200, 200), glm::vec2(100, 50), glm::vec4(0.8f, 0.2f, 0.2f, 1.0f));

		while (!m_Window->ShouldWindowClose())
		{
			glfwPollEvents();
			InputManager::Update();

			// This will sort all UI elements based on their z order
			UIElementsManager::GetInstance().SortElements();

			// Update UI
			UIElementsManager::GetInstance().UpdateElements();

			if (myButton.Clicked())
			{
				std::cout << "Button " << myButton.GetIdentifier() << " clicked!" << std::endl;
			}

			// Rendering
			Renderer2D::BeginScene(m_OrthographicCamera);

			// This will call Draw on all UI elements
			UIElementsManager::GetInstance().DrawElements();

			Renderer2D::EndScene();
			glfwSwapBuffers(m_Window->GetGlfwWindow());
		}
	}

	Window* Application::GetWindow()
	{
		return m_Window;
	}
}