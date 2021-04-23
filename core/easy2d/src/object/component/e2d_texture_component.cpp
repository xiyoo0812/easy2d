#include "e2d_sprite_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_render_batch.h"

/* Easy2D */
using namespace Easy2D;

SpriteComponent::SpriteComponent(const String& name) : Component(name)
{
    mSpriteInfo = std::make_shared<RenderTexture>();
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::initialize()
{
}

void SpriteComponent::setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY)
{
    if (mTexture)
    {
        int32 w = mTexture->getWidth();
        int32 h = mTexture->getHeight();
        mSpriteInfo->mUvCoords = Vec4(beginX / w, beginY / h, endX / w, endY / h);
    }
}

void SpriteComponent::setUVCoords(const Vec4& coords)
{
    setUVCoords(coords.x, coords.y, coords.z, coords.w);
}

void SpriteComponent::update(const uint32& escapeMs)
{
    if (mTexture)
    {
        mSpriteInfo->mTransform = getTransform();
        RenderBatch::getInstance()->addRenderQueue(mSpriteInfo);
    }
}

void SpriteComponent::setColor(const Color & color)
{
    mSpriteInfo->mColor = color;
}

const Color& SpriteComponent::getColor() const
{
    return mSpriteInfo->mColor;
}

void SpriteComponent::setHUDEnabled(bool enabled)
{
    mSpriteInfo->mbHud = enabled;
}

bool SpriteComponent::isHUDEnabled() const
{
    return mSpriteInfo->mbHud;
}

void SpriteComponent::setTexture(SPtr<Texture2D> texture)
{
    mDimensions.x = 0;
    mDimensions.y = 0;
    mTexture = texture;

    mDimensions.x = texture->getWidth() / mWidthSegments;
    mDimensions.y = texture->getHeight() / mHeightSegments;

    getTransform()->setDimensions(mDimensions);
    mSpriteInfo->mTextureID = mTexture->getTextureID();
    mSpriteInfo->mVertices = Vec2(mDimensions.x, mDimensions.y);
}
