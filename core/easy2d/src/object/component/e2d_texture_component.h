#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "base/e2d_color.h"
#include "object/e2d_component.h"
#include "graphics/e2d_texture2d.h"
#include "graphics/e2d_render_object.h"

namespace Easy2D
{
    class SpriteComponent : public Component
    {
    public:
        SpriteComponent(const String& name);

        virtual ~SpriteComponent();

        virtual void initialize();

        virtual void update(const uint32& escapeMs);

        void setColor(const Color& color);
        
        const Color& getColor() const;

        void setHUDEnabled(bool enabled);

        bool isHUDEnabled() const;

        void setUVCoords(const Vec4& coords);

        void setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY);

        void setTexture(SPtr<Texture2D> mTexture);

    private:
        SPtr<Texture2D> mTexture = nullptr;
        SPtr<RenderTexture> mSpriteInfo = nullptr;
    };
}

#endif
