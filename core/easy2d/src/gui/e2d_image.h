#ifndef IMAGE_H
#define IMAGE_H

#include "e2d_widget.h"
#include "base/e2d_color.h"
#include "graphics/e2d_texture2d.h"

namespace Easy2D
{
    class SpriteComponent;
    class UIImage : public UIWidget
    {
    public:
        UIImage(const String& name, uint32 horizontalSegements = 1, uint32 verticalSegments = 1);

        virtual ~UIImage();

        virtual void setHorizontalAlignment(HorizontalAlignment alignment, bool redefineCenter = true);
        virtual void setVerticalAlignment(VerticalAlignment alignment, bool redefineCenter = true);

        void setCurrentSegement(uint32 segmentX, uint32 segmentY);

        void setColor(const Color& color);

        void setTexture(SPtr<Texture2D> mTexture, uint32 widthSegments = 1, uint32 heightSegments = 1);

        virtual Vec2 getDimensions() const;

        float32 getWidth() const;
        float32 getHeight() const;

    protected:
        SPtr<SpriteComponent> mSpriteComponent;
    };
}

#endif
