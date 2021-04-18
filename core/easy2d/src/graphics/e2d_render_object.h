#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "base/e2d_color.h"

namespace Easy2D
{
    class Font;
    class TransformComponent;

    enum RenderSortingMode
    {
        BackFront = 0,
        FrontBack,
    };

    class RenderObject
    {
    public:
        bool mbHud = false;
        Color mColor = Color::White;
        SPtr<TransformComponent> mTransform = nullptr;
    };

    class RenderSprite : public RenderObject
    {
    public:
        Vec2 mVertices = {};
        Vec4 mUvCoords = {};
        uint32 mTextureID = 0;
    };

    class RenderText : public RenderObject
    {
    public:
        Wtring mText = L"";
        uint16 mSpacing = 0;
        uint16 mTextHeight = 10;
        uint16 mShadowSize = 0;
        uint16 mOutlineSize = 0;
        Color mShadowColor = Color::Black;
        Color mOutlineColor = Color::Black;
        Vector<uint16> mAlianOffset = {};
        SPtr<Font> mFont = nullptr;
        bool mbItalic = false;
        bool mbBold = false;
    };
}

#endif
