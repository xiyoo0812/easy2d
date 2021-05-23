#include "e2d_image.h"
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

UIImage::~UIImage(void)
{

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

bool UIImage::isScale9Tile() const
{
    return mTextureComponent->isScale9Tile();
}

const Vec4i& UIImage::getScale9Tile() const
{
    return mTextureComponent->getScale9Tile();
}

void UIImage::setScale9Tile(const Vec4i& tiles)
{
    mTextureComponent->setScale9Tile(tiles.x, tiles.y, tiles.z, tiles.w);
}

void UIImage::setScale9Tile(const uint32 beginX, uint32 beginY, uint32 endX, uint32 endY)
{
    mTextureComponent->setScale9Tile(beginX, beginY, endX, endY);
}

