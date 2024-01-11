#include "Window.h"
#include <Event System/EventManager.h>
#include <Event System/Event/Events/WindowResizeEvent.h>

namespace Visionary
{
	Window::Window(const char* title, int width, int height)
	{
        m_GlfwWindow = glfwCreateWindow(width, height, title, NULL, NULL);

        if (!m_GlfwWindow)
        {
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_GlfwWindow);

        // Inside the Window constructor
        glfwSetWindowSizeCallback(m_GlfwWindow, [](GLFWwindow* window, int width, int height)
        {
                auto event = std::make_shared<WindowResizeEvent>(width, height);
                EventManager::Get().DispatchEvent(event);
        });
	}

	Window::~Window()
	{
        
	}

    bool Window::ShouldWindowClose()
    {
        return glfwWindowShouldClose(m_GlfwWindow);
    }

    void Window::SetShouldWindowClose(bool value)
    {
        glfwSetWindowShouldClose(m_GlfwWindow, value ? 1 : 0);
    }

	void Window::DisableDefaultTitleBar()
	{
        HWND hWnd = glfwGetWin32Window(m_GlfwWindow);

        LONG_PTR lStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
        lStyle |= WS_THICKFRAME;
        lStyle &= ~WS_CAPTION;
        SetWindowLongPtr(hWnd, GWL_STYLE, lStyle);

        RECT windowRect;
        GetWindowRect(hWnd, &windowRect);
        int width = windowRect.right - windowRect.left;
        int height = windowRect.bottom - windowRect.top;

        m_OriginalProc = (WNDPROC)SetWindowLongPtr(hWnd, GWLP_WNDPROC, (LONG_PTR)StaticWindowProc);
        SetWindowPos(hWnd, NULL, 0, 0, width, height, SWP_FRAMECHANGED | SWP_NOMOVE);
	}

    GLFWwindow* Window::GetGlfwWindow()
    {
        return m_GlfwWindow;
    }

    glm::vec2 Window::GetWindowSize()
    {
        int width, height;
        glfwGetWindowSize(m_GlfwWindow, &width, &height);
        return glm::vec2(width, height);
    }

    LRESULT CALLBACK Window::StaticWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        Window* window;
        if (uMsg == WM_NCCREATE)
        {
            window = static_cast<Window*>(((LPCREATESTRUCT)lParam)->lpCreateParams);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
        }
        else
        {
            window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        }

        if (window)
        {
            return window->WindowProc(hWnd, uMsg, wParam, lParam);
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    LRESULT CALLBACK Window::Window::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        switch (uMsg)
        {
        case WM_NCCALCSIZE:
        {
            // Remove the window's standard sizing border
            if (wParam == TRUE && lParam != NULL)
            {
                NCCALCSIZE_PARAMS* pParams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
                pParams->rgrc[0].top += 1;
                pParams->rgrc[0].right -= 2;
                pParams->rgrc[0].bottom -= 2;
                pParams->rgrc[0].left += 2;
            }
            return 0;
        }
        case WM_NCPAINT:
        {
            // Prevent the non-client area from being painted
            return 0;
        }
        case WM_NCHITTEST:
        {
            // Expand the hit test area for resizing
            const int borderWidth = 8; // Adjust this value to control the hit test area size

            POINTS mousePos = MAKEPOINTS(lParam);
            POINT clientMousePos = { mousePos.x, mousePos.y };
            ScreenToClient(hWnd, &clientMousePos);

            RECT windowRect;
            GetClientRect(hWnd, &windowRect);

            if (clientMousePos.y >= windowRect.bottom - borderWidth)
            {
                if (clientMousePos.x <= borderWidth)
                    return HTBOTTOMLEFT;
                else if (clientMousePos.x >= windowRect.right - borderWidth)
                    return HTBOTTOMRIGHT;
                else
                    return HTBOTTOM;
            }
            else if (clientMousePos.y <= borderWidth)
            {
                if (clientMousePos.x <= borderWidth)
                    return HTTOPLEFT;
                else if (clientMousePos.x >= windowRect.right - borderWidth)
                    return HTTOPRIGHT;
                else
                    return HTTOP;
            }
            else if (clientMousePos.x <= borderWidth)
            {
                return HTLEFT;
            }
            else if (clientMousePos.x >= windowRect.right - borderWidth)
            {
                return HTRIGHT;
            }

            break;
        }
        }

        return CallWindowProc(m_OriginalProc, hWnd, uMsg, wParam, lParam);
    }
}