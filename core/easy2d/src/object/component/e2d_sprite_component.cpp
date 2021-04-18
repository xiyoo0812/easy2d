#include "e2d_sprite_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_render_batch.h"

/* Easy2D */
using namespace Easy2D;

SpriteComponent::SpriteComponent(uint32 widthSegments, uint32 heightSegments)
    : Component(SpriteComponent::GUID), mWidthSegments(widthSegments), mHeightSegments(heightSegments)
{
    mSpriteInfo = std::make_shared<RenderSprite>();
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::initialize()
{
}

void SpriteComponent::fillSpriteInfo()
{
    mSpriteInfo->mTransform = getTransform();
    mSpriteInfo->mTextureID = mTexture->getTextureID();
    mSpriteInfo->mVertices = Vec2(mDimensions.x, mDimensions.y);
}

void SpriteComponent::createUVCoords()
{
    float32 startX = float32(mCurrentWidthSegment) / float32(mWidthSegments);
    float32 endX = 1.0f / mWidthSegments;
    float32 startY = float32(mCurrentHeightSegment) / float32(mHeightSegments);
    float32 endY = 1.0f / mHeightSegments;

    setUVCoords(Vec4(startX, startY, endX, endY));
}

void SpriteComponent::setUVCoords(const Vec4& coords)
{
    mSpriteInfo->mUvCoords = coords;
}

void SpriteComponent::draw()
{
    RenderBatch::getInstance()->addRenderQueue(mSpriteInfo);
}

void SpriteComponent::update(const uint32& escapeMs)
{
#ifdef ANDROID
    fillSpriteInfo();
#endif
}

bool SpriteComponent::checkCulling(float32 left, float32 right, float32 top, float32 bottom) const
{
    //Always draw hudObjects
    if (mSpriteInfo->mbHud)
    {
        return true;
    }
    float32 spriteWidth, spriteHeight;
    Vec2 objectPos = getTransform()->getWorldPosition();
    if (mSpriteInfo->mbHud)
    {
        objectPos.x += left;
        objectPos.y += bottom;
    }
    spriteWidth = float32(getWidth()) * getTransform()->getWorldScale().x;
    spriteHeight = float32(getHeight()) * getTransform()->getWorldScale().y;
    float32 objRight = objectPos.x + spriteWidth;
    float32 objTop = objectPos.y + spriteHeight;

    return (objectPos.x <= right && objRight >= left) && (objectPos.y <= top && objTop >= bottom);
}

void SpriteComponent::setCurrentSegment(uint32 widthSegment, uint32 heightSegment)
{
    mCurrentWidthSegment = widthSegment;
    mCurrentHeightSegment = mHeightSegments - heightSegment - 1;
    createUVCoords();
}

void SpriteComponent::setColor(const Color & color)
{
    mSpriteInfo->mColor = color;
}

const Color& SpriteComponent::getColor() const
{
    return mSpriteInfo->mColor;
}

void SpriteComponent::setHUDOptionEnabled(bool enabled)
{
    mSpriteInfo->mbHud = enabled;
}

bool SpriteComponent::isHUDOptionEnabled() const
{
    return mSpriteInfo->mbHud;
}

void SpriteComponent::setTexture(SPtr<Texture2D> texture, uint32 widthSegments /* = 1 */, uint32 heightSegments /* = 1 */)
{
    mDimensions.x = 0;
    mWidthSegments = widthSegments;
    mCurrentWidthSegment = 0;
    mDimensions.y = 0;
    mHeightSegments = heightSegments;
    mCurrentHeightSegment = 0;
    mTexture = texture;

    mDimensions.x = texture->getWidth() / mWidthSegments;
    mDimensions.y = texture->getHeight() / mHeightSegments;

    getTransform()->setDimensionsSafe(mDimensions);

    createUVCoords();
    fillSpriteInfo();
}
