#ifndef VERTIX_RECT_H
#define VERTIX_RECT_H

#include "base\e2d_types.h"

namespace Easy2D
{
    class VertixRect
    {
    public:
        VertixRect() {}
        VertixRect(const Vec2& bl, const Vec2& size);
        VertixRect(const Vec4& tl, const Vec4& tr, const Vec4& bl, const Vec4& br);

        VertixRect operator=(const VertixRect& yRef);

        float32 getWidth() const;
        float32 getHeight() const;

        const Vec4& getTopLeft() const;
        const Vec4& getTopRight() const;
        const Vec4& getBottomLeft() const;
        const Vec4& getBottomRight() const;

        void mul(const Mat4& mat);
        void buildRect(const Vec2& bl, const Vec2& size, const Mat4& mat);

        bool posInRect(const Vec2& pos) const;
        Vec2 pos2Ratio(const Vec2& pos) const;

        Vector<Vec4> mVectics;
        Vec2 mSize;
    };
}

#endif
