#pragma once

#include "sepch.h"

namespace Shushao {

    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPressed,
        KeyReleased,
        KeyTyped,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum class EventCategory : int
    {
        None = 0,
        Application = BIT(1),
        Input = BIT(2),
        Keyboard = BIT(3),
        Mouse = BIT(4),
        MouseButton = BIT(5)
    };

    ENABLE_BITMASK_OPERATORS(EventCategory);

    #define EVENT_CLASS_TYPE(type)                                                  \
        static EventType GetStaticType() { return EventType::type; }                \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

    #define EVENT_CLASS_CATEGORY(category) \
        virtual EventCategory GetCategoryFlags() const override { return category; }

    class Event
    {
    public:
        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual EventCategory GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return static_cast<bool>(GetCategoryFlags() & category);
        }
    };

    class EventDispatcher
    {
        template <typename T>
        using EventFunction = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& event) : event(event) {}

        template <typename T>
        bool Dispatch(EventFunction<T> function)
        {
            if (event.GetEventType() == T::GetStaticType()) {
                event.Handled = function(*(T*)&event);
                return true;
            }
            return false;
        }

    private:
        Event& event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}  // namespace se
