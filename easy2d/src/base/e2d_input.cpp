#include "e2d_input.h"

/* Easy2D */
using namespace Easy2D;

//--------------------------------------------------------------------------------
void OnChar(GLFWwindow* window, unsigned int codepoint)
{
    auto event = std::make_shared<KeyEvent>(KeyType::Char);
    event->mKey = codepoint;
    InputSystem::instance()->handleInput(event);
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    KeyType kType = (action == GLFW_RELEASE) ? KeyType::KeyUp : KeyType::KeyDown;
    auto event = std::make_shared<KeyEvent>(KeyType(kType));
    event->mSysKey = scancode;
    event->mKey = key;
    InputSystem::instance()->handleInput(event);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button >= GLFW_MOUSE_BUTTON_LEFT && button <= GLFW_MOUSE_BUTTON_MIDDLE)
    {
        double x = 0, y = 0;
        MouseType mType = (MouseType)(button * 2 + action);
        auto event = std::make_shared<MouseEvent>(mType);
        glfwGetCursorPos(window, (double*)&x, (double*)&y);
        event->mPos = Vec2(x, y);
        InputSystem::instance()->handleInput(event);
    }
}

void OnMouseMove(GLFWwindow* window, double x, double y)
{
    auto event = std::make_shared<MouseEvent>(MouseType::MouseMove);
    event->mPos.x = x;
    event->mPos.y = y;
    InputSystem::instance()->handleInput(event);
}

void OnMouseWheel(GLFWwindow* window, double x, double y)
{
    double xp = 0, yp = 0;
    auto event = std::make_shared<MouseEvent>(MouseType::MouseWheel);
    event->mWheelX = x;
    event->mWheelY = y;
    glfwGetCursorPos(window, (double*)&xp, (double*)&yp);
    event->mPos = Vec2(xp, yp);
    InputSystem::instance()->handleInput(event);
}

//--------------------------------------------------------------------------------
void InputSystem::initialize(GLFWwindow* window)
{
    glfwSetKeyCallback(window, OnKey);
    glfwSetCharCallback(window, OnChar);
    glfwSetMouseButtonCallback(window, OnMouseButton);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetScrollCallback(window, OnMouseWheel);
}

bool InputSystem::addInputSink(SPtr<InputSink> sink)
{
    auto pair = mInputSinks.insert(sink);
    return pair.second;
}

void InputSystem::handleInput(SPtr<KeyEvent> event)
{
    for (auto sink : mInputSinks)
    {
        if (sink->handleInput(event) == BubbleType::Break)
        {
            break;
        }
    }
}

void InputSystem::handleInput(SPtr<MouseEvent> event)
{
    for (auto sink : mInputSinks)
    {
        if (sink->handleInput(event) == BubbleType::Break)
        {
            break;
        }
    }
}

//--------------------------------------------------------------------------------
BubbleType InputSink::handleInput(SPtr<KeyEvent> event)
{
    VisibleType vType = VisibleType::Visible;
    if (enableInput(event, vType) == BubbleType::Return)
    {
        return BubbleType::Continue;
    }
    if (vType == VisibleType::HitChild || vType == VisibleType::Visible)
    {
        if (handleChildInput(event) == BubbleType::Break)
        {
            return BubbleType::Break;
        }
    }
    BubbleType bubble = BubbleType::Continue;
    if (vType == VisibleType::HitSelf || vType == VisibleType::Visible)
    {
        switch (event->mType)
        {
        case KeyType::KeyUp:
            bubble = onKeyUp(std::dynamic_pointer_cast<KeyEvent>(event));
            break;
        case KeyType::KeyDown:
            bubble = onKeyDown(std::dynamic_pointer_cast<KeyEvent>(event));
            break;
        case KeyType::Char:
            bubble = onChar(std::dynamic_pointer_cast<KeyEvent>(event));
            break;
        }
    }
    return bubble;
}

BubbleType InputSink::handleInput(SPtr<MouseEvent> event)
{
    VisibleType vType = VisibleType::Visible;
    if (enableInput(event, vType) == BubbleType::Return)
    {
        return BubbleType::Continue;
    }
    if (vType == VisibleType::HitChild || vType == VisibleType::Visible)
    {
        if (handleChildInput(event) == BubbleType::Break)
        {
            return BubbleType::Break;
        }
    }
    BubbleType bubble = BubbleType::Continue;
    switch (event->mType)
    {
    case MouseType::LButtonUp:
        bubble = onLButtonUp(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::RButtonUp:
        bubble = onRButtonUp(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::MButtonUp:
        bubble = onMButtonUp(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::LButtonDown:
        bubble = onLButtonDown(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::RButtonDown:
        bubble = onRButtonDown(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::MButtonDown:
        bubble = onMButtonDown(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::MouseMove:
        bubble = onMouseMove(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    case MouseType::MouseWheel:
        bubble = onMouseWheel(std::dynamic_pointer_cast<MouseEvent>(event));
        break;
    }
    return bubble;
}

BubbleType InputSink::enableInput(SPtr<KeyEvent> event, VisibleType& visable)
{
    return BubbleType::Continue;
}

BubbleType InputSink::enableInput(SPtr<MouseEvent> event, VisibleType& visable)
{
    return BubbleType::Continue;
}

BubbleType InputSink::handleChildInput(SPtr<KeyEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::handleChildInput(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onKeyUp(SPtr<KeyEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onKeyDown(SPtr<KeyEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onChar(SPtr<KeyEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onLButtonUp(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onRButtonUp(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onMButtonUp(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onLButtonDown(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onRButtonDown(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onMButtonDown(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onMouseMove(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

BubbleType InputSink::onMouseWheel(SPtr<MouseEvent> event)
{
    return BubbleType::Continue;
}

void Easy2D::InputSink::onMouseEnter(SPtr<MouseEvent> event)
{
    
}

void Easy2D::InputSink::onMouseLeave(SPtr<MouseEvent> event)
{
}
