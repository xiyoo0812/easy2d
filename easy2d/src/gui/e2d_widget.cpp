#include "e2d_widget.h"
#include "base/e2d_input.h"

/* Easy2D */
using namespace Easy2D;

//------------------------------------------------------------------------------
UIWidget::UIWidget(const String& name) : Entity(name)
{

}

UIWidget::~UIWidget()
{
}

BubbleType UIWidget::onMouseMove(SPtr<MouseEvent> event)
{
    bool inRect = isInRect(event->mPos);
    if (mbMouseHover && !inRect)
    {
        onMouseLeave(event);
    }
    if (!mbMouseHover && inRect)
    {
        onMouseEnter(event);
    }
    setMouseHover(inRect);
    return BubbleType::Continue;
}

//------------------------------------------------------------------------------
UIRoot::UIRoot() : UIWidget(GUID)
{

}

bool UIRoot::setup()
{
    if (!Entity::setup())
    {
        LOG_WARN << _T("UIRoot::setup: Entity setup failed!");
        return false;
    }
    setDockerAlign(DockerAlign::Full);
    InputSystem::instance()->addInputSink(std::dynamic_pointer_cast<InputSink>(shared_from_this()));
    return true;
}

BubbleType Easy2D::UIRoot::handleInput(SPtr<KeyEvent> event)
{
    if (mInputFocus && mInputFocus->handleInput(event) == BubbleType::Break)
    {
        return BubbleType::Break;
    }
    return InputSink::handleInput(event);
}

BubbleType Easy2D::UIRoot::onLButtonUp(SPtr<MouseEvent> event)
{
    if (mInputFocus && !mInputFocus->isInRect(event->mPos))
    {
        mInputFocus->onLButtonUp(event);
        mInputFocus = nullptr;
    }
    return BubbleType::Continue;
}

void Easy2D::UIRoot::setInputFocus(SPtr<UIWidget> widget)
{
    mInputFocus = widget;
}
