#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>
#include "Event/Event.h"

namespace Visionary
{
    using EventCallback = std::function<void(const std::shared_ptr<Event>&)>;

    class EventManager 
    {
    public:
        static EventManager& Get() 
        {
            static EventManager instance;
            return instance;
        }

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;

        template<typename T>
        void RegisterEvent(std::function<void(const T&)> callback, void* owner);

        template<typename T>
        void UnregisterEvent(void* owner);

        void DispatchEvent(const std::shared_ptr<Event>& event);

    private:
        struct EventCallbackWrapper 
        {
            EventCallback callback;
            void* owner;

            EventCallbackWrapper(EventCallback callback, void* owner)
                : callback(std::move(callback)), owner(owner) {}
        };

        std::unordered_map<std::type_index, std::vector<EventCallbackWrapper>> eventCallbacks;

        EventManager() = default;
        ~EventManager() = default;
    };

    template<typename T>
    void EventManager::RegisterEvent(std::function<void(const T&)> callback, void* owner) 
    {
        EventCallback wrapper = [callback](const std::shared_ptr<Event>& event) 
        {
            if (auto castedEvent = std::dynamic_pointer_cast<T>(event)) 
            {
                callback(*castedEvent);
            }
        };

        eventCallbacks[std::type_index(typeid(T))].push_back(EventCallbackWrapper(wrapper, owner));
    }

    template<typename T>
    void EventManager::UnregisterEvent(void* owner) 
    {
        auto& callbacks = eventCallbacks[std::type_index(typeid(T))];
        callbacks.erase(
            std::remove_if(callbacks.begin(), callbacks.end(), [owner](const EventCallbackWrapper& wrapper) {
                return wrapper.owner == owner;
                }),
            callbacks.end());
    }
}