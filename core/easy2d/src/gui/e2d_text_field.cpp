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
            getTransform()->setCenterX(0);
            mTextComponent->alignTextLeft();
            break;
        case HorizontalAlignment::Center:
            getTransform()->setCenterX(float32(mTextComponent->getWidth()) / 2.0f);
            mTextComponent->alignTextCenter();
            break;
        case HorizontalAlignment::Right:
            getTransform()->setCenterX(float32(mTextComponent->getWidth()));
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
            getTransform()->setCenterY(0);
            break;
        case VerticalAlignment::Center:
            getTransform()->setCenterY(float32(mTextComponent->getHeight()) / 2.0f);
            break;
        case VerticalAlignment::Top:
            getTransform()->setCenterY(float32(mTextComponent->getHeight()));
            break;
        }
    }
    UIWidget::setVerticalAlignment(alignment, redefineCenter);
}

void UITextField::setText(const String& text)
{
    mTextComponent->setText(text);
}

const String& UITextField::getText() const
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
