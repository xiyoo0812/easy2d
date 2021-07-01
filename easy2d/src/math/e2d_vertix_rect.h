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

        void mul(const Mat4& mat);

        float32 getWidth() const;
        float32 getHeight() const;
        const Vec2& getSize() const;

        const Vec4& getTopLeft() const;
        const Vec4& getTopRight() const;
        const Vec4& getBottomLeft() const;
        const Vec4& getBottomRight() const;
        const Vector<Vec4>& getVectics() const;

        bool posInRect(const Vec2& pos) const;

    private:
        Vector<Vec4> mVectics;
        Vec2 mSize;
    };
}

#endif
