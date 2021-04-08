#include "e2d_image.h"
#include "object/component/e2d_sprite_component.h"
#include "object/component/e2d_transform_component.h"

/* Easy2D */
using namespace Easy2D;

UIImage::UIImage(const String& name, uint32 horizontalSegements, uint32 verticalSegments)
    : UIWidget(name)
{
    mSpriteComponent = std::make_shared<SpriteComponent>(horizontalSegements, verticalSegments);
    mSpriteComponent->setHUDOptionEnabled(true);
    addComponent(mSpriteComponent);
}

UIImage::~UIImage(void)
{

}

void UIImage::setHorizontalAlignment(HorizontalAlignment alignment, bool redefineCenter)
{
    if (redefineCenter)
    {
        switch (alignment)
        {
        case HorizontalAlignment::Left:
            getTransform()->setCenterX(0);
            break;
        case HorizontalAlignment::Center:
            getTransform()->setCenterX(float32(mSpriteComponent->getWidth()) / 2.0f);
            break;
        case HorizontalAlignment::Right:
            getTransform()->setCenterX(float32(mSpriteComponent->getWidth()));
            break;
        }
    }
    UIWidget::setHorizontalAlignment(alignment, redefineCenter);
}

void UIImage::setVerticalAlignment(VerticalAlignment alignment, bool redefineCenter)
{
    if (redefineCenter)
    {
        switch (alignment)
        {
        case VerticalAlignment::Bottom:
            getTransform()->setCenterY(0);
            break;
        case VerticalAlignment::Center:
            getTransform()->setCenterY(float32(mSpriteComponent->getHeight()) / 2.0f);
            break;
        case VerticalAlignment::Top:
            getTransform()->setCenterY(float32(mSpriteComponent->getHeight()));
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
