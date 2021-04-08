#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "base/e2d_color.h"
#include "object/e2d_component.h"
#include "graphics/e2d_texture2d.h"

namespace Easy2D
{
    class SpriteInfo
    {
    public:
        Vec2 vertices = {};
        Vec4 uvCoords = {};
        bool bIsHud = false;
        uint32 textureID = 0;
        Color colorMultiplier = Color::White;
        SPtr<TransformComponent> transform = nullptr;
    };

    class SpriteComponent : public Component
    {
    public:
        SpriteComponent(uint32 widthSegments = 1, uint32 heightSegments = 1);

        virtual ~SpriteComponent();

        virtual void draw();

        virtual void initialize();

        virtual void update(const uint32& escapeMs);

        virtual bool checkCulling(float32 left, float32 right, float32 top, float32 bottom) const;

        void setCurrentSegment(uint32 widthSegment, uint32 heightSegment);

        void setColor(const Color& color);
        
        const Color& getColor() const;

        void setHUDOptionEnabled(bool enabled);

        bool isHUDOptionEnabled() const;

        void setTexture(SPtr<Texture2D> mTexture, uint32 widthSegments = 1, uint32 heightSegments = 1);

    protected:
        virtual void createUVCoords();
        void setUVCoords(const Vec4& coords);
        virtual void fillSpriteInfo();

        uint32 mWidthSegments = 0, mHeightSegments = 0;
        uint32 mCurrentWidthSegment = 0, mCurrentHeightSegment = 0;

    private:
        SPtr<Texture2D> mTexture = nullptr;
        SPtr<SpriteInfo> mSpriteInfo = nullptr;

    public:
        inline static String GUID = "sprite";
    };
}

#endif
