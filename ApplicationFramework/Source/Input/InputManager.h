#pragma once

#include <glm/glm.hpp>
#include <utility>
#include <unordered_map>
#include "Key.h" 
#include "MouseButton.h"

namespace Visionary 
{
    class InputManager 
    {
    public:
        static void Update();
        static bool IsKeyPressed(Key key);
        static bool IsKeyHeld(Key key);
        static void SetWindow(GLFWwindow* window);
        static glm::vec2 GetMousePosition();
        static bool IsMouseButtonPressed(MouseButton button);
        static bool IsMouseButtonHeld(MouseButton button);

    private:
        static GLFWwindow* window;
        static std::unordered_map<int, bool> currentKeyStates;
        static std::unordered_map<int, bool> previousKeyStates;
        static std::unordered_map<int, bool> currentMouseButtonStates;
        static std::unordered_map<int, bool> previousMouseButtonStates;

        static bool GetKeyState(Key key);
    };
}