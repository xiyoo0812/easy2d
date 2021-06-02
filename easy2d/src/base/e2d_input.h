#pragma once

#include "e2d_event.h"

namespace Easy2D
{
    enum class KeyType
    {
        KeyUp = GLFW_RELEASE,
        KeyDown,
        Char,
    };
    enum class MouseType
    {
        LButtonUp,
        LButtonDown,
        RButtonUp,
        RButtonDown,
        MButtonUp,
        MButtonDown,
        MouseMove,
        MouseWheel,
    };

    //-------------------------------------------------------------------------------
    class KeyEvent : public Event
    {
    public:
        KeyEvent(KeyType type) : Event(GUID), mType(type){}
        ~KeyEvent() {}

        uint16 mKey = 0, mSysKey = 0;
        KeyType mType = KeyType::KeyDown;
        inline static String GUID = "key_event";
    };

    //-------------------------------------------------------------------------------
    class MouseEvent : public Event
    {
    public:
        MouseEvent(MouseType type) : Event(GUID), mType(type) {}
        ~MouseEvent() {}

        MouseType mType = MouseType::MouseMove;
        double mX = 0, mY = 0, mWheelX, mWheelY = 0;
        inline static String GUID = "mouse_event";
    };

    //-------------------------------------------------------------------------------
    class InputSystem final : public EventSinkDispatcher, public Singleton<InputSystem>
    {
    public:
        friend Singleton<InputSystem>;

        InputSystem() {}
        ~InputSystem() {}

        void initialize(GLFWwindow* window);
    };
}
