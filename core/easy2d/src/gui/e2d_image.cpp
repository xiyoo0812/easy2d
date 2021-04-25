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
