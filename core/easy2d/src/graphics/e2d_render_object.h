#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "base/e2d_color.h"

namespace Easy2D
{
    class Font;
    class TransformComponent;

    enum RenderSortingMode
    {
        BACK_FRONT,
        FRONT_BACK,
    };

    enum class RenderObjectType
    {
        RENDER_SPRITE = 0,
        RENDER_TEXT,
    };

    class RenderObject
    {
    public:
        bool mbHud = false;
        Color mColor = Color::White;
        SPtr<TransformComponent> mTransform = nullptr;
        RenderObjectType mType = RenderObjectType::RENDER_SPRITE;

        RenderObject(RenderObjectType t) : mType(t){}
        virtual ~RenderObject(){}
    };

    class RenderSprite : public RenderObject
    {
    public:
        Vec2 mVertices = {};
        Vec4 mUvCoords = {};
        uint32 mTextureID = 0;
        RenderSprite(RenderObjectType t = RenderObjectType::RENDER_SPRITE) : RenderObject(t) {}
        virtual ~RenderSprite() {}
    };

    class RenderText : public RenderObject
    {
    public:
        Wtring mText = L"";
        int32 mSpacing = 0;
        int32 mTextHeight = 10;
        Vector<int32> mTextOffset = {};
        SPtr<Font> mFont = nullptr;

        RenderText(RenderObjectType t = RenderObjectType::RENDER_TEXT) : RenderObject(t) {}
        virtual ~RenderText() {}
    };
}

#endif
