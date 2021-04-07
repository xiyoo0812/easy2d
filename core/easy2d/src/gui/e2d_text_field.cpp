#include "e2d_text_field.h"
#include "object/omponent/e2d_text_component.h"

/* Easy2D */
using namespace Easy2D;

UITextField::UITextField(String& name,const String& text, const Color& color)
	: UIObject(name)
{
	mTextComponent = std::make_shared<TextComponent>();
	addComponent(mTextComponent);

	mTextComponent->setText(text);
	mTextComponent->setColor(color);
	mTextComponent->setHUDOptionEnabled(true);
}

UITextField::UITextField(const String& name, const String& text, const Color& color, SPtr<Font> font)
	: UIObject(name)
{
	mTextComponent = std::make_shared<TextComponent>();
	addComponent(mTextComponent);

	mTextComponent->setText(text);
	mTextComponent->setFont(font);
	mTextComponent->setColor(color);
	mTextComponent->setHUDOptionEnabled(true);
}

UITextField::~UITextField(void)
{
	mTextComponent->reset();
}

void UITextField::setHorizontalAlignment(HorizontalAlignment alignment,bool redefineCenter)
{
	if(redefineCenter)
	{
		switch(alignment)
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
	UIObject::setHorizontalAlignment(alignment,redefineCenter);
}

void UITextField::setVerticalAlignment(VerticalAlignment alignment,bool redefineCenter)
{
	if(redefineCenter)
	{
		switch(alignment)
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
	UIObject::setVerticalAlignment(alignment,redefineCenter);
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

void UITextField::setFont(const SPtr<Font>& font)
{
	mTextComponent->setFont(font);
}

const SPtr<Font> UITextField::getFont() const
{
    return mTextComponent->getFont();
}

vec2 UITextField::getDimensions() const
{
	return Vec2(getWidth(), getHeight());
}

int32 UITextField::getWidth() const
{
	return mTextComponent->getWidth();
}

int32 UITextField::getHeight() const
{
	return mTextComponent->getHeight();
}
