#include "e2d_sprite_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_sprite_batch.h"
#include "graphics/e2d_texture_mgr.h"

/* Easy2D */
using namespace Easy2D;

SpriteComponent::SpriteComponent(const String& filepath, const String& spriteName, uint32 widthSegments, uint32 heightSegments)
    : Component(), mFilePath(filepath), mSpriteName(spriteName)
{
    mSpriteInfo = std::make_shared<SpriteInfo>();
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::initialize()
{
    TextureManager::getInstance()->loadTexture(mFilePath.string(), mSpriteName);

    mDimensions.x = TextureManager::getInstance()->getTextureDimensions(mSpriteName).x / mWidthSegments;
    mDimensions.y = TextureManager::getInstance()->getTextureDimensions(mSpriteName).y / mHeightSegments;

    getTransform()->setDimensionsSafe(mDimensions);

    createUVCoords();
    fillSpriteInfo();
}

void SpriteComponent::fillSpriteInfo()
{
    mSpriteInfo->transform = getTransform();
    mSpriteInfo->textureID = TextureManager::getInstance()->getTextureID(mSpriteName);
    mSpriteInfo->vertices = Vec2(mDimensions.x, mDimensions.y);
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
    mSpriteInfo->uvCoords = coords;
}

void SpriteComponent::draw()
{
    SpriteBatch::getInstance()->addSpriteToQueue(mSpriteInfo);
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
    if (mSpriteInfo->bIsHud)
    {
        return true;
    }

    float32 spriteWidth, spriteHeight;

    Pos objectPos = getTransform()->getWorldPosition();

    if (mSpriteInfo->bIsHud)
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

const Path& SpriteComponent::getFilePath() const
{
    return mFilePath;
}

const String& SpriteComponent::getName() const
{
    return mSpriteName;
}

void SpriteComponent::setCurrentSegment(uint32 widthSegment, uint32 heightSegment)
{
    mCurrentWidthSegment = widthSegment;
    mCurrentHeightSegment = mHeightSegments - heightSegment - 1;
    createUVCoords();
}

void SpriteComponent::setColorMultiplier(const Color & color)
{
    mSpriteInfo->colorMultiplier = color;
}

void SpriteComponent::setHUDOptionEnabled(bool enabled)
{
    mSpriteInfo->bIsHud = enabled;
}

bool SpriteComponent::isHUDOptionEnabled() const
{
    return mSpriteInfo->bIsHud;
}

void SpriteComponent::setTexture(const String& filepath, const String& spriteName, uint32 widthSegments /* = 1 */, uint32 heightSegments /* = 1 */)
{
    mDimensions.x = 0;
    mWidthSegments = widthSegments;
    mCurrentWidthSegment = 0;
    mDimensions.y = 0;
    mHeightSegments = heightSegments;
    mCurrentHeightSegment = 0;
    mFilePath = filepath;
    mSpriteName = spriteName;

    TextureManager::getInstance()->loadTexture(mFilePath.string(), mSpriteName);
    mDimensions.x = TextureManager::getInstance()->getTextureDimensions(mSpriteName).x / mWidthSegments;
    mDimensions.y = TextureManager::getInstance()->getTextureDimensions(mSpriteName).y / mHeightSegments;

    getTransform()->setDimensionsSafe(mDimensions);

    createUVCoords();
    fillSpriteInfo();
}
