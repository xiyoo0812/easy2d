#ifndef RECT_H
#define RECT_H

#include "base\e2d_types.h"

namespace Easy2D
{
    class Rect
    {
    public:
        Rect() {}
        Rect(const Vec2& leftTop, const Vec2& size);
        Rect operator=(const Rect& yRef);

        Rect operator*(float32 constant) const;
        Rect operator/(float32 constant) const;
        Rect& operator*=(float32 constant);

        float32 getWidth() const;
        float32 getHeight() const;

        const Vec2& getLeftTop() const;

        Vec2 getCenterPoint() const;
        bool posInRect(const Vec2& pos) const;

        void setPoints(const Vec2& leftTop, const Vec2& rightBottom);
        void setLeftTop(const Vec2& leftTop);
        void setRightBottom(const Vec2& rightBottom);

        Vec2 mLeftTop;
        Vec2 mSize;
    };
}

#endif
