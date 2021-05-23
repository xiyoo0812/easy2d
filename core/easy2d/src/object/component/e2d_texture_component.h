#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include "base/e2d_color.h"
#include "object/e2d_component.h"
#include "graphics/e2d_texture2d.h"
#include "graphics/e2d_render_object.h"

namespace Easy2D
{
    class TextureComponent : public Component
    {
    public:
        TextureComponent();

        virtual ~TextureComponent();

        virtual void initialize();

        virtual void update(const uint32& escapeMs);

        virtual void onHandleEvent(SPtr<Event> event);

        void setColor(const Color& color);
        
        const Color& getColor() const;

        void setHUDEnabled(bool enabled);

        bool isHUDEnabled() const;

        bool isScale9Tile() const;

        const Vec4i& getScale9Tile() const;

        void setScale9Tile(const Vec4i& tiles);

        void setScale9Tile(const uint32 beginX, uint32 beginY, uint32 endX, uint32 endY);

        void setUVCoords(const Vec4& coords);

        void setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY);

        void setTexture(SPtr<Texture2D> mTexture);

    private:
        SPtr<Texture2D> mTexture = nullptr;
        SPtr<RenderTexture> mRenderTex = nullptr;

    public:
        inline static String GUID = "render_texture";
    };
}

#endif
