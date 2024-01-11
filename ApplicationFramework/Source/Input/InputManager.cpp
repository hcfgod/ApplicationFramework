#include "InputManager.h"

namespace Visionary 
{
    GLFWwindow* InputManager::window = nullptr;
    std::unordered_map<int, bool> InputManager::currentKeyStates;
    std::unordered_map<int, bool> InputManager::previousKeyStates;
    std::unordered_map<int, bool> InputManager::currentMouseButtonStates;
    std::unordered_map<int, bool> InputManager::previousMouseButtonStates;

    void InputManager::Update() 
    {
        previousKeyStates = currentKeyStates;
        // Update currentKeyStates for all keys you're interested in
        for (const auto& keyPair : currentKeyStates) 
        {
            currentKeyStates[keyPair.first] = GetKeyState(static_cast<Key>(keyPair.first));
        }

        // Update mouse button states
        for (const auto& buttonPair : currentMouseButtonStates) 
        {
            previousMouseButtonStates[buttonPair.first] = buttonPair.second;
            currentMouseButtonStates[buttonPair.first] = glfwGetMouseButton(window, buttonPair.first) == GLFW_PRESS;
        }
    }

    bool InputManager::IsKeyPressed(Key key) 
    {
        return currentKeyStates[static_cast<int>(key)] && !previousKeyStates[static_cast<int>(key)];
    }

    bool InputManager::IsKeyHeld(Key key) 
    {
        return currentKeyStates[static_cast<int>(key)];
    }

    void InputManager::SetWindow(GLFWwindow* newWindow) 
    {
        window = newWindow;
    }

    bool InputManager::GetKeyState(Key key) 
    {
        if (window == nullptr) 
        {
            return false;
        }
        return glfwGetKey(window, static_cast<int>(key)) == GLFW_PRESS;
    }

    glm::vec2 InputManager::GetMousePosition() 
    {
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        // Get window size
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        // Convert to your coordinate system
        y = height - y;

        return glm::vec2(x, y);
    }

    bool InputManager::IsMouseButtonPressed(MouseButton button) 
    {
        int buttonInt = static_cast<int>(button);
        return currentMouseButtonStates[buttonInt] && !previousMouseButtonStates[buttonInt];
    }

    bool InputManager::IsMouseButtonHeld(MouseButton button) 
    {
        return currentMouseButtonStates[static_cast<int>(button)];
    }
}