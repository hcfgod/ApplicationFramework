#pragma once

#include "../Event.h"
#include <string>

namespace Visionary
{
    class OnButtonClickEvent : public Event
    {
    public:
        OnButtonClickEvent(const std::string& buttonId) : m_ButtonId(buttonId) {}

        const std::string& GetButtonId() const { return m_ButtonId; }

    private:
        std::string m_ButtonId;
    };
}