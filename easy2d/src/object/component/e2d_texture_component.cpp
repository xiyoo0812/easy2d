#include "e2d_texture_component.h"
#include "e2d_transform_component.h"
#include "object/e2d_entity.h"
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

bool TextureComponent::setup(SPtr<Entity> master)
{
    setMaster(master);
    master->addTrigger(TransformEvent::GUID, std::dynamic_pointer_cast<EventListerner>(shared_from_this()));
    return true;
}

void TextureComponent::setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY)
{
    if (mTexture)
    {
        int32 w = mTexture->getWidth();
        int32 h = mTexture->getHeight();
        mUvCoords = Vec4(beginX / w, beginY / h, endX / w, endY / h);
        mbChanged = true;
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
        if (mbChanged)
        {
            if (mScale9Enable)
            {
                mRenderTexScale9.clear();
                uint32 w = mTexture->getWidth();
                uint32 h = mTexture->getHeight();
                float32 endCoordX = w - mScale9Tile.z / w;
                float32 endCorrdY = h - mScale9Tile.w / h;
                auto& transDim = getTransform()->getSize();
                auto& matWorld = getTransform()->getWorldMatrix();
                uint32 centerWidth = transDim.x - mScale9Tile.x - mScale9Tile.z;
                uint32 centerHeight = transDim.y - mScale9Tile.y - mScale9Tile.w;
                auto renderTexTL = buildRenderTexture(Vec4(mUvCoords.x, endCorrdY, mScale9Tile.x / w, mUvCoords.w));
                auto renderTexTC = buildRenderTexture(Vec4(mScale9Tile.x / w, endCorrdY, endCoordX, mUvCoords.w));
                auto renderTexTR = buildRenderTexture(Vec4(endCoordX, endCorrdY, mUvCoords.z, mUvCoords.w));
                auto renderTexCL = buildRenderTexture(Vec4(mUvCoords.x, mScale9Tile.y / h, mScale9Tile.x / w, endCorrdY));
                auto renderTexCC = buildRenderTexture(Vec4(mScale9Tile.x / w, mScale9Tile.y / h, endCoordX, endCorrdY));
                auto renderTexCR = buildRenderTexture(Vec4(endCoordX, mScale9Tile.y / h, mUvCoords.z, endCorrdY));
                auto renderTexBL = buildRenderTexture(Vec4(mUvCoords.x, mUvCoords.y, mScale9Tile.x / w, mScale9Tile.y / h));
                auto renderTexBC = buildRenderTexture(Vec4(mScale9Tile.x / w, mUvCoords.y, endCoordX, mScale9Tile.y / h));
                auto renderTexBR = buildRenderTexture(Vec4(endCoordX, mUvCoords.y, mUvCoords.z, mScale9Tile.y / h));
                renderTexTL->mVexRect = VertixRect(Vec2(0), Vec2(mScale9Tile.x, mScale9Tile.y));
                renderTexTL->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(0, 0, 0))));
                renderTexTC->mVexRect = VertixRect(Vec2(0), Vec2(centerWidth, mScale9Tile.y));
                renderTexTC->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(mScale9Tile.x, 0, 0))));
                renderTexTR->mVexRect = VertixRect(Vec2(0), Vec2(mScale9Tile.z, mScale9Tile.y));
                renderTexTR->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(transDim.x - mScale9Tile.z, 0, 0))));
                renderTexCL->mVexRect = VertixRect(Vec2(0), Vec2(mScale9Tile.x, centerHeight));
                renderTexCL->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(0, mScale9Tile.y, 0))));
                renderTexCC->mVexRect = VertixRect(Vec2(0), Vec2(centerWidth, centerHeight));
                renderTexCC->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(mScale9Tile.x, mScale9Tile.y, 0))));
                renderTexCR->mVexRect = VertixRect(Vec2(0), Vec2(mScale9Tile.z, centerHeight));
                renderTexCR->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(transDim.x - mScale9Tile.z, mScale9Tile.y, 0))));
                renderTexBL->mVexRect = VertixRect(Vec2(0), Vec2(mScale9Tile.x, mScale9Tile.w));
                renderTexBL->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(0, transDim.y - mScale9Tile.w, 0))));
                renderTexBC->mVexRect = VertixRect(Vec2(0), Vec2(centerWidth, mScale9Tile.w));
                renderTexBC->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(mScale9Tile.x, transDim.y - mScale9Tile.w, 0))));
                renderTexBR->mVexRect = VertixRect(Vec2(0), Vec2(mScale9Tile.z, mScale9Tile.w));
                renderTexBR->mVexRect.mul(Easy2D::transpose(matWorld * Easy2D::translate(Vec3(transDim.x - mScale9Tile.z, transDim.y - mScale9Tile.w, 0))));
            }
            else
            {
                mRenderTex->buildUvCooreds(mUvCoords);
                mRenderTex->mVexRect = getTransform()->getVertices();
            }
            mbChanged = false;
        }
        if (mRenderTexScale9.size() > 0)
        {
            for (auto renderTex : mRenderTexScale9)
            {
                RenderBatch::instance()->addRenderQueue(renderTex);
            }
            return;
        }
        RenderBatch::instance()->addRenderQueue(mRenderTex);
    }
}

bool TextureComponent::isScale9Tile() const
{
    return mScale9Enable;
}

void TextureComponent::disableScale9Tile()
{
    mScale9Enable = false;
}

const Vec4& TextureComponent::getScale9Tile() const
{
    return mScale9Tile;
}

void TextureComponent::setScale9Tile(const Vec4& tiles)
{
    setScale9Tile(tiles.x, tiles.y, tiles.z, tiles.w);
}

void TextureComponent::setScale9Tile(const float32 beginX, float32 beginY, float32 endX, float32 endY)
{
    if (mTexture)
    {
        mScale9Tile = Vec4i(beginX, beginY, endX, endY);
        mScale9Enable = true;
        mbChanged = true;
    }
}

SPtr<RenderTexture> TextureComponent::buildRenderTexture(const Vec4& uvCoords)
{
    auto renderTex = std::make_shared<RenderTexture>();
    renderTex->mbHud = mRenderTex->mbHud;
    renderTex->mColor = mRenderTex->mColor;
    renderTex->mTextureID = mRenderTex->mTextureID;
    renderTex->buildUvCooreds(uvCoords);
    mRenderTexScale9.push_back(renderTex);
    return renderTex;
}

void TextureComponent::onHandleEvent(SPtr<Event> event)
{
    if (event->getGuid() == TransformEvent::GUID)
    {
        mbChanged = true;
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
    mbChanged = true;
    mTexture = texture;
    auto transDim = getTransform()->getSize();
    if (transDim.x <= 1 && transDim.y <= 1)
    {
        getTransform()->setSize(texture->getWidth(), texture->getHeight());
    }
    mRenderTex->mTextureID = mTexture->getTextureID();
}
