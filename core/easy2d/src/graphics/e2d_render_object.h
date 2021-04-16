#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "base/e2d_color.h"

namespace Easy2D
{
    class Font;
    class TransformComponent;

    enum RenderSortingMode
    {
        BackFront,
        FrontBack,
    };

    enum class RenderObjectType
    {
        ObjectSprite = 0,
        ObjectText,
    };

    class RenderObject
    {
    public:
        bool mbHud = false;
        Color mColor = Color::White;
        SPtr<TransformComponent> mTransform = nullptr;
        RenderObjectType mType = RenderObjectType::ObjectSprite;

        RenderObject(RenderObjectType t) : mType(t){}
        virtual ~RenderObject(){}
    };

    class RenderSprite : public RenderObject
    {
    public:
        Vec2 mVertices = {};
        Vec4 mUvCoords = {};
        uint32 mTextureID = 0;
        RenderSprite(RenderObjectType t = RenderObjectType::ObjectSprite) : RenderObject(t) {}
        virtual ~RenderSprite() {}
    };

    class RenderText : public RenderObject
    {
    public:
        Wtring mText = L"";
        uint16 mSpacing = 0;
        uint16 mShadowSize = 0;
        uint16 mTextHeight = 10;
        Color mShadowColor = Color::Black;
        Vector<uint16> mAlianOffset = {};
        SPtr<Font> mFont = nullptr;
        bool mbItalic = false;
        bool mbBold = false;

        RenderText(RenderObjectType t = RenderObjectType::ObjectText) : RenderObject(t) {}
        virtual ~RenderText() {}
    };
}

#endif
