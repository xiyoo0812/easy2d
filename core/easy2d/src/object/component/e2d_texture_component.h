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

        void disableScale9Tile();

        const Vec4& getScale9Tile() const;

        void setScale9Tile(const Vec4& tiles);

        void setScale9Tile(const float32 beginX, float32 beginY, float32 endX, float32 endY);

        void setUVCoords(const Vec4& coords);

        void setUVCoords(float32 beginX, float32 beginY, float32 endX, float32 endY);

        void setTexture(SPtr<Texture2D> mTexture);

    protected:
        SPtr<RenderTexture> buildRenderTexture();

    private:
        Vec4 mScale9Tile { 0, 0, 1, 1 };
        SPtr<Texture2D> mTexture = nullptr;
        SPtr<RenderTexture> mRenderTex = nullptr;
        Vector<SPtr<RenderTexture>> mRenderTexScale9 = {};

    public:
        inline static String GUID = "render_texture";
    };
}

#endif
