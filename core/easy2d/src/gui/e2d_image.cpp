#include "e2d_image.h"
#include "object/component/e2d_texture_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UIImage::UIImage(const String& name)
    : UIWidget(name)
{
    mTextureComponent = std::make_shared<TextureComponent>();
    mTextureComponent->setHUDEnabled(true);
    addComponent(mTextureComponent);
}

UIImage::~UIImage(void)
{

}

void UIImage::setHorizontalAlignment(HorizontalAlign alignment, bool redefineCenter)
{
    if (redefineCenter)
    {
        switch (alignment)
        {
        case HorizontalAlign::Left:
            getTransform()->setAnchorX(0);
            break;
        case HorizontalAlign::Center:
            getTransform()->setAnchorX(0.5);
            break;
        case HorizontalAlign::Right:
            getTransform()->setAnchorX(1);
            break;
        }
    }
    UIWidget::setHorizontalAlignment(alignment, redefineCenter);
}

void UIImage::setVerticalAlignment(VerticalAlign alignment, bool redefineCenter)
{
    if (redefineCenter)
    {
        switch (alignment)
        {
        case VerticalAlign::Bottom:
            getTransform()->setAnchorY(0);
            break;
        case VerticalAlign::Center:
            getTransform()->setAnchorY(0.5);
            break;
        case VerticalAlign::Top:
            getTransform()->setAnchorY(1);
            break;
        }
    }
    UIWidget::setVerticalAlignment(alignment, redefineCenter);
}

void UIImage::setTexture(SPtr<Texture2D> mTexture)
{
    mTextureComponent->setTexture(mTexture);
}

void UIImage::setColor(const Color& color)
{
    mTextureComponent->setColor(color);
}
