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

        const Color& getColor() const;

        void setTexture(SPtr<Texture2D> mTexture);

        bool isScale9Tile() const;

        const Vec4i& getScale9Tile() const;

        void setScale9Tile(const Vec4i& tiles);

        void setScale9Tile(const uint32 beginX, uint32 beginY, uint32 endX, uint32 endY);

    protected:
        SPtr<TextureComponent> mTextureComponent;
    };
}

#endif
