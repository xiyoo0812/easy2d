#pragma once

#include "e2d_event.h"

namespace Easy2D
{
    enum class BubbleType
    {
        //ֹͣ����
        Break,
        //��������
        Continue,
        //�����ϲ㣬��������
        Return,
    };

    enum class VisibleType
    {
        //���Ӳ������¼�
        Visible,
        //���ز������¼�
        Hidden,
        //��ʾ���������¼����Լ����ӽڵ㣩
        NotHitAll,
        //��ʾ���������¼������Լ���
        NotHitSelfOnly,
    };

    enum class KeyType
    {
        KeyUp = 0,
        KeyDown,
        Char,
    };

    enum class MouseType
    {
        LButtonUp = 0,
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
        KeyEvent(KeyType type) : Event(GUID), mType(type) {}
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

        Vec2 mPos;
        double mWheelX, mWheelY = 0;
        MouseType mType = MouseType::LButtonUp;
        inline static String GUID = "mouse_event";
    };

    //-------------------------------------------------------------------------------
    class InputSink
    {
    public:
        virtual BubbleType handleInput(SPtr<KeyEvent> event);
        virtual BubbleType handleInput(SPtr<MouseEvent> event);
        virtual BubbleType handleInputBefor(SPtr<KeyEvent> event, VisibleType& visable);
        virtual BubbleType handleInputBefor(SPtr<MouseEvent> event, VisibleType& visable);
        virtual BubbleType handleChildInput(SPtr<KeyEvent> event);
        virtual BubbleType handleChildInput(SPtr<MouseEvent> event);
        virtual BubbleType onKeyUp(SPtr<KeyEvent> event);
        virtual BubbleType onKeyDown(SPtr<KeyEvent> event);
        virtual BubbleType onChar(SPtr<KeyEvent> event);
        virtual BubbleType onLButtonUp(SPtr<MouseEvent> event);
        virtual BubbleType onRButtonUp(SPtr<MouseEvent> event);
        virtual BubbleType onMButtonUp(SPtr<MouseEvent> event);
        virtual BubbleType onLButtonDown(SPtr<MouseEvent> event);
        virtual BubbleType onRButtonDown(SPtr<MouseEvent> event);
        virtual BubbleType onMButtonDown(SPtr<MouseEvent> event);
        virtual BubbleType onMouseMove(SPtr<MouseEvent> event);
        virtual BubbleType onMouseWheel(SPtr<MouseEvent> event);
    };

    //-------------------------------------------------------------------------------
    class InputSystem final : public Singleton<InputSystem>
    {
    public:
        friend Singleton<InputSystem>;

        InputSystem() {}
        ~InputSystem() {}

        void initialize(GLFWwindow* window);

        bool addInputSink(SPtr<InputSink> sink);

        void handleInput(SPtr<KeyEvent> event);
        void handleInput(SPtr<MouseEvent> event);

    private:
        Set<SPtr<InputSink>> mInputSinks;
    };
}
