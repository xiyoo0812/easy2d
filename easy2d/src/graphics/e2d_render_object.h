#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "base/e2d_color.h"
#include "math/e2d_vertix_rect.h"

namespace Easy2D
{
    class Font;
    class TransformComponent;

    class RenderObject
    {
    public:
        bool mbHud = false;
        Color mColor = Color::White;
    };

    class RenderRect : public RenderObject
    {
    public:
        VertixRect mVexRect;
    };

    class RenderTexture : public RenderRect
    {
    public:
        uint32 mTextureID = 0;
        Vector<Vec2> mUvCoords{};

        void buildUvCooreds(Vec4 uvcoods)
        {
            /*
            *  TL    TR
            *   0----1
            *   |   /|
            *   |  / |
            *   | /  |
            *   |/   |
            *   2----3
            *  BL    BR
            */
            mUvCoords = 
            {
                //0123
                Vec2(uvcoods.x, uvcoods.y),
                Vec2(uvcoods.z, uvcoods.y),
                Vec2(uvcoods.x, uvcoods.w),
                Vec2(uvcoods.z, uvcoods.w)
            };
        }
    };

    class RenderText : public RenderObject
    {
    public:
        Mat4 matWorld{};
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
