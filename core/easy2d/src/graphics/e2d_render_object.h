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
        int32 mOffsetY = 0;
        bool mbHud = false;
        Color mColor = Color::White;
        SPtr<TransformComponent> mTransform = nullptr;
    };

    class RenderTexture : public RenderObject
    {
    public:
        Vec4 mUvCoords{ 0, 0, 1, 1 };
        Vec4i mScale9{ 0, 0, 1, 1 };
        Vec2i mVertices{ 1, 1 };
        uint32 mTextureID = 0;

        bool isScale9Tile() const
        {
            return mScale9.x > 0 && mScale9.y > 0 && mScale9.z < mVertices.x && mScale9.w < mVertices.y;
        }

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
