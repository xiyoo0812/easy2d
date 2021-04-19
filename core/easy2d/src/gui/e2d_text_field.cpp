#include "e2d_text_field.h"
#include "object/component/e2d_text_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UITextField::UITextField(const String& name)
    : UIWidget(name)
{
    mTextComponent = std::make_shared<TextComponent>();
    addComponent(mTextComponent);
}

UITextField::~UITextField(void)
{
}

void UITextField::initialize()
{
    Entity::initialize();
    mTextComponent->setHUDOptionEnabled(true);
}

void UITextField::setHorizontalAlignment(HorizontalAlignment alignment, bool redefineCenter)
{
    if (redefineCenter)
    {
        switch (alignment)
        {
        case HorizontalAlignment::Left:
            getTransform()->setAnchorX(0);
            mTextComponent->alignTextLeft();
            break;
        case HorizontalAlignment::Center:
            getTransform()->setAnchorX(0.5);
            mTextComponent->alignTextCenter();
            break;
        case HorizontalAlignment::Right:
            getTransform()->setAnchorX(1);
            mTextComponent->alignTextRight();
            break;
        }
    }
    UIWidget::setHorizontalAlignment(alignment, redefineCenter);
}

void UITextField::setVerticalAlignment(VerticalAlignment alignment, bool redefineCenter)
{
    if (redefineCenter)
    {
        switch (alignment)
        {
        case VerticalAlignment::Bottom:
            getTransform()->setAnchorY(0);
            break;
        case VerticalAlignment::Center:
            getTransform()->setAnchorY(0.5);
            break;
        case VerticalAlignment::Top:
            getTransform()->setAnchorY(1);
            break;
        }
    }
    UIWidget::setVerticalAlignment(alignment, redefineCenter);
}

void UITextField::setText(const Wtring& text)
{
    mTextComponent->setText(text);
}

const Wtring& UITextField::getText() const
{
    return mTextComponent->getText();
}

void UITextField::setColor(const Color& color)
{
    mTextComponent->setColor(color);
}

const Color& UITextField::getColor() const
{
    return mTextComponent->getColor();
}

void UITextField::setShadowColor(const Color& color, uint16 shodowSize /* = 1 */)
{
    mTextComponent->setShadowColor(color, shodowSize);
}

const Color& UITextField::getShadowColor() const
{
    return mTextComponent->getShadowColor();
}

void UITextField::setOutlineColor(const Color& color, uint16 outlineSize /* = 1 */)
{
    mTextComponent->setOutlineColor(color, outlineSize);
}

const Color& UITextField::getOutlineColor() const
{
    return mTextComponent->getOutlineColor();
}

void UITextField::setBold(bool bold)
{
    mTextComponent->setBold(bold);
}

bool UITextField::isBold() const
{
    return mTextComponent->isBold();
}

void UITextField::setItalic(bool italoc)
{
    mTextComponent->setItalic(italoc);
}

bool UITextField::isItalic() const
{
    return mTextComponent->isItalic();
}

void UITextField::setFont(const SPtr<Font> font)
{
    mTextComponent->setFont(font);
}

const SPtr<Font> UITextField::getFont() const
{
    return mTextComponent->getFont();
}

Vec2 UITextField::getDimensions() const
{
    return Vec2(getWidth(), getHeight());
}

float32 UITextField::getWidth() const
{
    return mTextComponent->getWidth();
}

float32 UITextField::getHeight() const
{
    return mTextComponent->getHeight();
}
