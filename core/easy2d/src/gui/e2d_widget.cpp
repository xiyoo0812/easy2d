#include "e2d_widget.h"
#include "graphics/e2d_graphics_mgr.h"

/* Easy2D */
using namespace Easy2D;

UIWidget::UIWidget(const String& name) : Entity(name)
{

}

UIWidget::~UIWidget()
{
}

void UIWidget::initialize()
{
    Entity::initialize();
    reposition();
    repositionChildren();
}


void UIWidget::setHorizontalAlignment(HorizontalAlign alignment, bool redefineCenter)
{
    mHorizontalAlignment = alignment;
    setPositionX(0);
}

void UIWidget::setVerticalAlignment(VerticalAlign alignment, bool redefineCenter)
{
    mVerticalAlignment = alignment;
    setPositionY(0);
}

void UIWidget::setAlignmentCentered(bool redefineCenter)
{
    setHorizontalAlignment(HorizontalAlign::Center, redefineCenter);
    setVerticalAlignment(VerticalAlign::Center, redefineCenter);
}

void UIWidget::reposition()
{
    //translate();
}

void UIWidget::update(const uint32& escapeMs)
{
    Entity::update(escapeMs);
}

void UIWidget::draw()
{
    Entity::draw();
}

void UIWidget::setRootWidget()
{
    mbRootWidget = true;
}

Vec2 UIWidget::getDockDimensions() const
{
    if (mbRootWidget)
    {
        return GraphicsManager::getInstance()->getScreenResolution();
    }
    if (mParent.expired())
    {
        return Vec2(0, 0);
    }
    return mParent.lock()->getDimensions();
}

void UIWidget::setPosition(const Vec2& translation)
{
    Entity::setPosition(translateUIX(translation.x), translateUIY(translation.y));
}

void UIWidget::setPosition(float32 x, float32 y)
{
    Entity::setPosition(translateUIX(x), translateUIY(y));
}

void UIWidget::setPositionX(float32 x)
{
    Entity::setPositionX(translateUIX(x));
}

void UIWidget::setPositionY(float32 y)
{
    Entity::setPositionY(translateUIY(y));
}

float32 UIWidget::translateUIX(float32 x)
{
    Vec2 dimensions = getDockDimensions();
    switch (mHorizontalAlignment)
    {
    case HorizontalAlign::Center:
        x += dimensions.x / 2;
        break;
    case HorizontalAlign::Right:
        x += dimensions.x;
        break;
    }
    return x;
}

float32 UIWidget::translateUIY(float32 y)
{
    Vec2 dimensions = getDockDimensions();
    switch (mVerticalAlignment)
    {
    case VerticalAlign::Center:
        y += dimensions.y / 2;
        break;
    case VerticalAlign::Top:
        y += dimensions.y;
        break;
    }
    return y;
}

void UIWidget::repositionChildren()
{
    for (auto child : mChildrens)
    {
        auto element = std::dynamic_pointer_cast<UIWidget>(child);
        if (element != nullptr)
        {
            element->reposition();
        }
    }
}

