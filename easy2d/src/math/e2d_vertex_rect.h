#ifndef VERTEX_RECT_H
#define VERTEX_RECT_H

#include "base\e2d_types.h"

namespace Easy2D
{
    class VertexRect
    {
    public:
        VertexRect() {}
        VertexRect(const Vec2& bl, const Vec2& size);
        VertexRect(const Vec4& tl, const Vec4& tr, const Vec4& bl, const Vec4& br);

        VertexRect operator=(const VertexRect& yRef);

        float32 getWidth() const;
        float32 getHeight() const;

        const Vec4& getTopLeft() const;
        const Vec4& getTopRight() const;
        const Vec4& getBottomLeft() const;
        const Vec4& getBottomRight() const;

        void transform(const Mat4& mat);
        void general(const Vec2& bl, const Vec2& size, const Mat4& mat);

        bool posInRect(const Vec2& pos) const;
        Vec2 pos2Ratio(const Vec2& pos) const;

        Vector<Vec4> mVertexs;
        Vec2 mSize;
    };
}

#endif
