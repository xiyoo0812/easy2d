#include "e2d_image.h"
#include "graphics/e2d_texture_mgr.h"
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

UIImage::~UIImage()
{

}

bool UIImage::loadTexture(const String& texPath)
{
    auto texture = TextureManager::getInstance()->loadTexture(texPath);
    if (nullptr == texture)
    {
        LOG_ERROR << "UIImage::setTexture error: texture(" << texPath << ") load failed!";
        return false;
    }
    setTexture(texture);
    return true;
}

void UIImage::setTexture(SPtr<Texture2D> mTexture)
{
    mTextureComponent->setTexture(mTexture);
}

void UIImage::setColor(const Color& color)
{
    mTextureComponent->setColor(color);
}

const Color& UIImage::getColor() const
{
    return mTextureComponent->getColor();
}

void UIImage::setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY)
{
    mTextureComponent->setUVCoords(beginX, beginY, endX, endY);
}

void UIImage::setUVCoords(const Vec4& coords)
{
    mTextureComponent->setUVCoords(coords.x, coords.y, coords.z, coords.w);
}

bool UIImage::isScale9Tile() const
{
    return mTextureComponent->isScale9Tile();
}

void UIImage::disableScale9Tile()
{
    mTextureComponent->disableScale9Tile();
}

const Vec4& UIImage::getScale9Tile() const
{
    return mTextureComponent->getScale9Tile();
}

void UIImage::setScale9Tile(const Vec4& tiles)
{
    mTextureComponent->setScale9Tile(tiles.x, tiles.y, tiles.z, tiles.w);
}

void UIImage::setScale9Tile(const float32 beginX, float32 beginY, float32 endX, float32 endY)
{
    mTextureComponent->setScale9Tile(beginX, beginY, endX, endY);
}

