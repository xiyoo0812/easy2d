#include "e2d_input.h"

/* Easy2D */
using namespace Easy2D;

void OnChar(GLFWwindow* window, unsigned int codepoint)
{
    auto event = std::make_shared<KeyEvent>(KeyType::Char);
    event->mKey = codepoint;
    InputSystem::getInstance()->onHandleEvent(event);
}

void OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto event = std::make_shared<KeyEvent>(KeyType(action));
    event->mSysKey = scancode;
    event->mKey = key;
    InputSystem::getInstance()->onHandleEvent(event);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    if (button >= GLFW_MOUSE_BUTTON_LEFT && button <= GLFW_MOUSE_BUTTON_MIDDLE)
    {
        MouseType mType = (MouseType)((button - 1) * 2 + action);
        auto event = std::make_shared<MouseEvent>(MouseType(action));
        glfwGetCursorPos(window, &event->mX, &event->mY);
        InputSystem::getInstance()->onHandleEvent(event);
    }
}

void OnMouseMove(GLFWwindow* window, double x, double y)
{
    auto event = std::make_shared<MouseEvent>(MouseType::MouseMove);
    event->mX = x;
    event->mY = y;
    InputSystem::getInstance()->onHandleEvent(event);
}

void OnMouseWheel(GLFWwindow* window, double x, double y)
{
    auto event = std::make_shared<MouseEvent>(MouseType::MouseWheel);
    event->mWheelX = x;
    event->mWheelY = y;
    glfwGetCursorPos(window, &event->mX, &event->mY);
    InputSystem::getInstance()->onHandleEvent(event);
}

void InputSystem::setup(GLFWwindow* window)
{
    glfwSetKeyCallback(window, OnKey);
    glfwSetCharCallback(window, OnChar);
    glfwSetMouseButtonCallback(window, OnMouseButton);
    glfwSetCursorPosCallback(window, OnMouseMove);
    glfwSetScrollCallback(window, OnMouseWheel);
}
