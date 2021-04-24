#include "e2d_texture_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_render_batch.h"

/* Easy2D */
using namespace Easy2D;

TextureComponent::TextureComponent() : Component(TextureComponent::GUID)
{
    mRenderTex = std::make_shared<RenderTexture>();
}

TextureComponent::~TextureComponent()
{
}

void TextureComponent::initialize()
{
}

void TextureComponent::setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY)
{
    if (mTexture)
    {
        int32 w = mTexture->getWidth();
        int32 h = mTexture->getHeight();
        mRenderTex->mUvCoords = Vec4(beginX / w, beginY / h, endX / w, endY / h);
    }
}

void TextureComponent::setUVCoords(const Vec4& coords)
{
    setUVCoords(coords.x, coords.y, coords.z, coords.w);
}

void TextureComponent::update(const uint32& escapeMs)
{
    if (mTexture)
    {
        mRenderTex->mTransform = getTransform();
        RenderBatch::getInstance()->addRenderQueue(mRenderTex);
    }
}

void TextureComponent::setColor(const Color & color)
{
    mRenderTex->mColor = color;
}

const Color& TextureComponent::getColor() const
{
    return mRenderTex->mColor;
}

void TextureComponent::setHUDEnabled(bool enabled)
{
    mRenderTex->mbHud = enabled;
}

bool TextureComponent::isHUDEnabled() const
{
    return mRenderTex->mbHud;
}

void TextureComponent::setTexture(SPtr<Texture2D> texture)
{
    mTexture = texture;
    Vec2 transDim = getTransform()->getDimensions();
    if (transDim.x == 0 && transDim.y == 0)
    {
        transDim = Vec2(texture->getWidth(), texture->getHeight());
        getTransform()->setDimensions(transDim);
    }
    mRenderTex->mTextureID = mTexture->getTextureID();
    mRenderTex->mVertices = transDim;
}
