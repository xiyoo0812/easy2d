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
            auto& pos = getTransform()->getPosition();
            auto& transDim = getTransform()->getSize();
            auto& matWorld = getTransform()->getWorldMatrix();
            uint32 windowHeight = GraphicsManager::getInstance()->getWindowHeight();
            if (mRenderTexScale9.size() > 0)
            {
                uint32 centerWidth = transDim.x - mScale9Tile.x - mScale9Tile.z;
                uint32 centerHeight = transDim.y - mScale9Tile.y - mScale9Tile.w;
                mRenderTexScale9[0]->mVertices = Vec2(mScale9Tile.x, mScale9Tile.y);    //tl
                mRenderTexScale9[0]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(0, 0, 0)));
                mRenderTexScale9[1]->mVertices = Vec2(centerWidth, mScale9Tile.y);      //tc
                mRenderTexScale9[1]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(mScale9Tile.x, 0, 0)));
                mRenderTexScale9[2]->mVertices = Vec2(mScale9Tile.z, mScale9Tile.y);    //tr
                mRenderTexScale9[2]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(transDim.x - mScale9Tile.z, 0, 0)));
                mRenderTexScale9[3]->mVertices = Vec2(mScale9Tile.x, centerHeight);     //cl
                mRenderTexScale9[3]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(0, mScale9Tile.y, 0)));
                mRenderTexScale9[4]->mVertices = Vec2(centerWidth, centerHeight);       //cc
                mRenderTexScale9[4]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(mScale9Tile.x, mScale9Tile.y, 0)));
                mRenderTexScale9[5]->mVertices = Vec2(mScale9Tile.z, centerHeight);     //cr
                mRenderTexScale9[5]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(transDim.x - mScale9Tile.z, mScale9Tile.y, 0)));
                mRenderTexScale9[6]->mVertices = Vec2(mScale9Tile.x, mScale9Tile.w);    //bl
                mRenderTexScale9[6]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(0, transDim.y - mScale9Tile.w, 0)));
                mRenderTexScale9[7]->mVertices = Vec2(centerWidth, mScale9Tile.w);      //bc
                mRenderTexScale9[7]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(mScale9Tile.x, transDim.y - mScale9Tile.w, 0)));
                mRenderTexScale9[8]->mVertices = Vec2(mScale9Tile.z, mScale9Tile.w);    //br
                mRenderTexScale9[8]->matWorld = Easy2D::transpose(matWorld * Easy2D::translate(Vec3(transDim.x - mScale9Tile.z, transDim.y - mScale9Tile.w, 0)));
            }
            else
            {
                mRenderTex->mVertices = transDim;
                mRenderTex->matWorld = matWorld;
            }
            mChanged = false;
        }
        if (mRenderTexScale9.size() > 0)
        {
            for (auto renderTex : mRenderTexScale9)
            {
                 RenderBatch::getInstance()->addRenderQueue(renderTex);
            }
            return;
        }
        RenderBatch::getInstance()->addRenderQueue(mRenderTex);
    }
}

bool TextureComponent::isScale9Tile() const
{
    return mRenderTexScale9.size() > 0;
}

void TextureComponent::disableScale9Tile()
{
    mScale9Tile = Vec4{ 0,0,1,1 };
    mRenderTexScale9.clear();
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
        uint32 w = mTexture->getWidth();
        uint32 h = mTexture->getHeight();
        float32 uvCoordsX = mRenderTex->mUvCoords.x;
        float32 uvCoordsY = mRenderTex->mUvCoords.y;
        float32 uvCoordsZ = mRenderTex->mUvCoords.z;
        float32 uvCoordsW = mRenderTex->mUvCoords.w;
        mScale9Tile = Vec4i(beginX, beginY, w - endX, h - endY);
        auto renderTexTL = buildRenderTexture();
        renderTexTL->mUvCoords = Vec4(uvCoordsX, endY / h, beginX / w, uvCoordsW);
        mRenderTexScale9.push_back(renderTexTL);
        auto renderTexTC = buildRenderTexture();
        renderTexTC->mUvCoords = Vec4(beginX / w, endY / h, endX / w, uvCoordsW);
        mRenderTexScale9.push_back(renderTexTC);
        auto renderTexTR = buildRenderTexture();
        renderTexTR->mUvCoords = Vec4(endX / w, endY / h, uvCoordsZ, uvCoordsW);
        mRenderTexScale9.push_back(renderTexTR);
        auto renderTexCL = buildRenderTexture();
        renderTexCL->mUvCoords = Vec4(uvCoordsX, beginY / h, beginX / w, endY / h);
        mRenderTexScale9.push_back(renderTexCL);
        auto renderTexCC = buildRenderTexture();
        renderTexCC->mUvCoords = Vec4(beginX / w, beginY / h, endX / w, endY / h);
        mRenderTexScale9.push_back(renderTexCC);
        auto renderTexCR = buildRenderTexture();
        renderTexCR->mUvCoords = Vec4(endX / w, beginY / h, uvCoordsZ, endY / h);
        mRenderTexScale9.push_back(renderTexCR);
        auto renderTexBL = buildRenderTexture();
        renderTexBL->mUvCoords = Vec4(uvCoordsX, uvCoordsY, beginX / w, beginY / h);
        mRenderTexScale9.push_back(renderTexBL);
        auto renderTexBC = buildRenderTexture();
        renderTexBC->mUvCoords = Vec4(beginX / w, uvCoordsY, endX / w, beginY / h);
        mRenderTexScale9.push_back(renderTexBC);
        auto renderTexBR = buildRenderTexture();
        renderTexBR->mUvCoords = Vec4(endX / w, uvCoordsY, uvCoordsZ, beginY / h);
        mRenderTexScale9.push_back(renderTexBR);
        mChanged = true;
    }
}


SPtr<RenderTexture> TextureComponent::buildRenderTexture()
{
    auto renderTex = std::make_shared<RenderTexture>();
    renderTex->mbHud = mRenderTex->mbHud;
    renderTex->mColor = mRenderTex->mColor;
    renderTex->mTextureID = mRenderTex->mTextureID;
    return renderTex;
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