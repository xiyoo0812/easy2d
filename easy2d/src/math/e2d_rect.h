#ifndef RECT_H
#define RECT_H

#include "base\e2d_types.h"

namespace Easy2D
{
    class Rect
    {
    public:
        Rect() {}
        Rect(const Vec2& leftTop, const Vec2& rightBottom);
        Rect operator=(const Rect& yRef);

        Rect operator*(float32 constant) const;
        Rect operator/(float32 constant) const;
        Rect& operator*=(float32 constant);

        float32 getWidth() const;
        float32 getHeight() const;

        const Vec2& getLeftTop() const;
        const Vec2& getRightBottom() const;

        Vec2 getCenterPoint() const;

        void setPoints(const Vec2& leftTop, const Vec2& rightBottom);
        void setLeftTop(const Vec2& pos);
        void setRightBottom(const Vec2& pos);

    private:
        Vec2 mLeftTop;
        Vec2 mRightBottom;

        float32 mWidth = 0.0f;
        float32 mHeight = 0.0f;
    };
}

#endif
