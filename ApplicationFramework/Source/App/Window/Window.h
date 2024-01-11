#pragma once

#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <GLM/ext/vector_float2.hpp>

namespace Visionary
{
	class Window
	{
	public:
		Window(const char* title, int width, int height);	
		~Window();

		bool ShouldWindowClose();
		void SetShouldWindowClose(bool value);

		void DisableDefaultTitleBar();

		GLFWwindow* GetGlfwWindow();

		glm::vec2 GetWindowSize();

	private:
		GLFWwindow* m_GlfwWindow = nullptr;
		WNDPROC m_OriginalProc = NULL;

		static LRESULT CALLBACK StaticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}