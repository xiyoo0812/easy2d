#include "e2d_texture_component.h"
#include "e2d_transform_component.h"
#include "graphics/e2d_render_batch.h"
#include "graphics/e2d_graphics_mgr.h"

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
    mRenderTex->mTransform = getTransform();
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
        if (mChanged)
        {
            Vec2 pos = getTransform()->getPosition();
            Vec2 transDim = getTransform()->getSize();
            mRenderTex->mVertices = transDim;
            mRenderTex->mOffsetY = GraphicsManager::getInstance()->getWindowHeight() - transDim.y - pos.y * 2;
            mChanged = false;
        }
        RenderBatch::getInstance()->addRenderQueue(mRenderTex);
    }
}

void TextureComponent::onHandleEvent(SPtr<Event> event)
{
    if (event->getGuid() == TransformEvent::GUID)
    {
        mChanged = true;
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
    mChanged = true;
    mTexture = texture;
    Vec2 transDim = getTransform()->getSize();
    if (transDim.x == 1 && transDim.y == 1)
    {
        transDim = Vec2(texture->getWidth(), texture->getHeight());
        getTransform()->setSize(transDim);
    }
    mRenderTex->mTextureID = mTexture->getTextureID();
}
