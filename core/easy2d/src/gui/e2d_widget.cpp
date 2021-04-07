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
    reposition();
    repositionChildren();
}


void UIWidget::setHorizontalAlignment(HorizontalAlignment alignment, bool redefineCenter)
{
    mHorizontalAlignment = alignment;
    //translateUIX(mPosition.x);
}

void UIWidget::setVerticalAlignment(VerticalAlignment alignment, bool redefineCenter)
{
    mVerticalAlignment = alignment;
    //translateUIX(mPosition.y);
}

void UIWidget::setAlignmentCentered(bool redefineCenter)
{
    setHorizontalAlignment(HorizontalAlignment::Center, redefineCenter);
    setVerticalAlignment(VerticalAlignment::Center, redefineCenter);
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

void UIWidget::translate(const Vec2& translation)
{
    Entity::translate(translateUIX(translation.x), translateUIY(translation.y));
}

void UIWidget::translate(float32 x, float32 y)
{
    Entity::translate(translateUIX(x), translateUIY(y));
}

void UIWidget::translate(const Vec2& translation, lay l)
{
    Entity::translate(translateUIX(translation.x), translateUIY(translation.y), l);
}

void UIWidget::translate(float32 x, float32 y, lay l)
{
    Entity::translate(translateUIX(x), translateUIY(y), l);
}

void UIWidget::translate(const Pos& pos2D)
{
    Entity::translate(translateUIX(pos2D.x), translateUIY(pos2D.y));
}

void UIWidget::translateX(float32 x)
{
    Entity::translateY(translateUIX(x));
}

void UIWidget::translateY(float32 y)
{
    Entity::translateY(translateUIY(y));
}

float32 UIWidget::translateUIX(float32 x)
{
    Vec2 dimensions = getDockDimensions();
    switch (mHorizontalAlignment)
    {
    case HorizontalAlignment::Center:
        x += dimensions.x / 2;
        break;
    case HorizontalAlignment::Right:
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
    case VerticalAlignment::Center:
        y += dimensions.y / 2;
        break;
    case VerticalAlignment::Top:
        y += dimensions.y;
        break;
    }
    return y;
}

void UIWidget::repositionChildren()
{
    for (auto child : mChildren)
    {
        auto element = std::dynamic_pointer_cast<UIWidget>(child.second);
        if (element != nullptr)
        {
            element->reposition();
        }
    }
}

