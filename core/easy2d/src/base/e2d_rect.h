#ifndef RECT_H
#define RECT_H

#include "base/e2d_math.h"

namespace Easy2D
{
    class Rect
    {
    public:
        Rect(){}
        Rect(const Vec2& leftBottom, const Vec2& rightBottom, const Vec2& leftTop, const Vec2& rightTop);
        Rect operator=(const Rect& yRef);

        Rect operator*(float32 constant) const;
        Rect operator/(float32 constant) const;
        Rect& operator*=(float32 constant);
        
        float32 getWidth() const;
        float32 getHeight() const;

        const Vec2& getLeftTop() const;
        const Vec2& getRightTop() const;
        const Vec2& getLeftBottom() const;
        const Vec2& getRightBottom() const;

        Vec2 getCenterPoint() const;

        float32 getRealLeft() const;
        float32 getRealRight() const;
        float32 getRealTop() const;
        float32 getRealBottom() const;

        void setPoints(const Vec2& leftBottom, const Vec2& rightBottom, const Vec2& leftTop, const Vec2& rightTop);
        void setLeftTop(const Vec2& pos);
        void setLeftBottom(const Vec2& pos);
        void setRightTop(const Vec2& pos);
        void setRightBottom(const Vec2& pos);

    private:
        Vec2 mLeftTop;
        Vec2 mRightTop;
        Vec2 mLeftBottom;
        Vec2 mRightBottom;

        float32 mWidth = 0.0f;
        float32 mHeight = 0.0f;
    };
}

#endif
