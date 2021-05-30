#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "base/e2d_color.h"

namespace Easy2D
{
    class Font;
    class TransformComponent;

    class RenderObject
    {
    public:
        bool mbHud = false;
        Color mColor = Color::White;
        Mat4 matWorld{};
    };

    class RenderRect : public RenderObject
    {
    public:
        Vec2 mVertices{ 1, 1 };
    };

    class RenderTexture : public RenderRect
    {
    public:
        Vec4 mUvCoords{ 0, 0, 1, 1 };
        uint32 mTextureID = 0;
    };

    class RenderText : public RenderObject
    {
    public:
        uint16 mSpacing = 1;
        uint16 mShadowSize = 0;
        uint16 mOutlineSize = 0;
        Vector<Wtring> mTextList = {};
        Vector<int16> mVerticalOffset = {};
        Vector<int16> mHorizontalOffset = {};
        Color mShadowColor = Color::Black;
        Color mOutlineColor = Color::Black;
        SPtr<Font> mFont = nullptr;
        bool mbItalic = false;
        bool mbBold = false;
    };
}

#endif
