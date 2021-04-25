#ifndef IMAGE_H
#define IMAGE_H

#include "e2d_widget.h"
#include "base/e2d_color.h"
#include "graphics/e2d_texture2d.h"

namespace Easy2D
{
    class TextureComponent;
    class UIImage : public UIWidget
    {
    public:
        UIImage(const String& name);

        virtual ~UIImage();

        void setColor(const Color& color);

        void setTexture(SPtr<Texture2D> mTexture);

    protected:
        SPtr<TextureComponent> mTextureComponent;
    };
}

#endif
