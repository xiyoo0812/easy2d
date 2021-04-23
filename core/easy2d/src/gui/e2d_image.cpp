#include "e2d_image.h"
#include "object/component/e2d_sprite_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UIImage::UIImage(const String& name, uint32 horizontalSegements, uint32 verticalSegments)
    : UIWidget(name)
{
    mSpriteComponent = std::make_shared<SpriteComponent>(horizontalSegements, verticalSegments);
    mSpriteComponent->setHUDEnabled(true);
    addComponent(mSpriteComponent);
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

void UIImage::setCurrentSegement(uint32 segmentX, uint32 segmentY)
{
    mSpriteComponent->setCurrentSegment(segmentX, segmentY);
}

void UIImage::setTexture(SPtr<Texture2D> mTexture, uint32 widthSegments, uint32 heightSegments)
{
    mSpriteComponent->setTexture(mTexture, widthSegments, heightSegments);
}

void UIImage::setColor(const Color& color)
{
    mSpriteComponent->setColor(color);
}

Vec2 UIImage::getDimensions() const
{
    return Vec2(getWidth(), getHeight());
}

float32 UIImage::getWidth() const
{
    return mSpriteComponent->getWidth();
}

float32 UIImage::getHeight() const
{
    return mSpriteComponent->getHeight();
}
