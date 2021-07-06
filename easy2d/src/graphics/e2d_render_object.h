#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include "base/e2d_color.h"
#include "graphics/e2d_font.h"

namespace Easy2D
{
    class RenderRect
    {
    public:
        bool mbHud = true;
        Vector<Vec4> mVectics;
        Color mColor = Color::White;

        void buildVectics(const Vec2& bl, const Vec2& size, const Mat4& mat)
        {
            mVectics =
            {
                Easy2D::mul(Vec4(bl.x, bl.y + size.y, 0, 1), mat),
                Easy2D::mul(Vec4(bl.x + size.x, bl.y + size.y, 0, 1), mat),
                Easy2D::mul(Vec4(bl.x, bl.y, 0, 1), mat),
                Easy2D::mul(Vec4(bl.x + size.x, bl.y, 0, 1), mat)
            };
        }
    };

    class RenderTexture : public RenderRect
    {
    public:
        uint32 mTextureID = 0;
        Vector<Vec2> mUvCoords{};

        void setUvCooreds(const Vec4& uvcoods)
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

    class RenderText
    {
    public:
        size_t mCount = 0;
        Vector<Color> mColors{};
        Vector<Vec4> mVectics{};
        Vector<Vec2> mUvCoords{};
        Vector<uint32> mTextureIDs{};

        void clear()
        {
            mCount = 0;
            mColors.clear();
            mVectics.clear();
            mUvCoords.clear();
            mTextureIDs.clear();
        }

        void pushChar(SPtr<FontChar> fChar, Color& color, const Vec4& offset, const Mat4& mat, uint16 fontHeight)
        {
            Vec2& size = fChar->vertexSize;
            Mat4 offsetMatrix = Easy2D::translate(offset.x + offset.z + fChar->letterSize.x, offset.y + offset.w - fChar->letterSize.y, 0);
            offsetMatrix *= Easy2D::translate(0, fontHeight / 2.0f, 0);
            offsetMatrix *= Easy2D::scale(1, -1, 1);
            offsetMatrix *= Easy2D::translate(0, fontHeight / -2.0f, 0);
            offsetMatrix = Easy2D::transpose(mat * offsetMatrix);
            Vector<Vec4> vertexs =
            {
                Easy2D::mul(Vec4(0, size.y, 0, 1), offsetMatrix),
                Easy2D::mul(Vec4(size.x, size.y, 0, 1), offsetMatrix),
                Easy2D::mul(Vec4(0, 0, 0, 1), offsetMatrix),
                Easy2D::mul(Vec4(size.x, 0, 0, 1), offsetMatrix)
            };
            Vector<Vec2> uvcoords =
            {
                Vec2(fChar->uvCoords.x, fChar->uvCoords.y),
                Vec2(fChar->uvCoords.z, fChar->uvCoords.y),
                Vec2(fChar->uvCoords.x, fChar->uvCoords.w),
                Vec2(fChar->uvCoords.z, fChar->uvCoords.w)
            };
            mTextureIDs.push_back(fChar->textureID);
            mColors.insert(mColors.end(), 4, color);
            mVectics.insert(mVectics.end(), vertexs.begin(), vertexs.end());
            mUvCoords.insert(mUvCoords.end(), uvcoords.begin(), uvcoords.end());
            mCount++;
        }
    };
}

#endif
