#include "e2d_text_field.h"
#include "object/component/e2d_text_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UITextField::UITextField(const String& name)
    : UIWidget(name)
{
    mTextComponent = std::make_shared<TextComponent>();
    mTextComponent->setHUDEnabled(true);
    addComponent(mTextComponent);
}

UITextField::~UITextField(void)
{
}

void UITextField::setHorizontalAlign(HorizontalAlign align)
{
    mTextComponent->setHorizontalAlign(align);
}

void UITextField::setVerticalAlign(VerticalAlign align)
{
    mTextComponent->setVerticalAlign(align);
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

void UITextField::setLineWrap(bool lineWrap)
{
    mTextComponent->setLineWrap(lineWrap);
}

bool UITextField::isLineWrap() const
{
    return mTextComponent->isLineWrap();
}

void UITextField::setSpacing(uint32 spacing)
{
    mTextComponent->setSpacing(spacing);
}

uint32 UITextField::getSpacing() const
{
    return mTextComponent->getSpacing();
}

void UITextField::setFont(const SPtr<Font> font)
{
    mTextComponent->setFont(font);
}

const SPtr<Font> UITextField::getFont() const
{
    return mTextComponent->getFont();
}

