#include "EventManager.h"

namespace Visionary
{
    void EventManager::DispatchEvent(const std::shared_ptr<Event>& event) {
        auto& callbacks = eventCallbacks[std::type_index(typeid(*event))];
        for (auto& wrapper : callbacks) {
            wrapper.callback(event);
        }
    }
}