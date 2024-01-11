#pragma once
#include <GLFW/glfw3.h>

namespace Visionary 
{
    enum class MouseButton 
    {
        LeftMouse = GLFW_MOUSE_BUTTON_1,
        RightMouse = GLFW_MOUSE_BUTTON_2,
        Button3 = GLFW_MOUSE_BUTTON_3,
        Button4 = GLFW_MOUSE_BUTTON_4,
        Button5 = GLFW_MOUSE_BUTTON_5,
        Button6 = GLFW_MOUSE_BUTTON_6,
        Button7 = GLFW_MOUSE_BUTTON_7,
        Button8 = GLFW_MOUSE_BUTTON_8,
        // ... Add more if you need to handle more buttons
        LastButton = GLFW_MOUSE_BUTTON_LAST
    };
}