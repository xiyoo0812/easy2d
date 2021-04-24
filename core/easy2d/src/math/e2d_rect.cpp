#include "e2d_rect.h"

using namespace Easy2D;

Rect::Rect(const Vec2& leftTop, const Vec2& rightBottom)
    : mLeftTop(leftTop)
    , mRightBottom(rightBottom)
{
    mWidth = rightBottom.x - mLeftTop.x;
    mHeight = rightBottom.y - mLeftTop.y;
}

Rect Rect::operator=(const Rect& yRef)
{
    mHeight = yRef.mHeight;
    mLeftTop = yRef.mLeftTop;
    mRightBottom = yRef.mRightBottom;
    mWidth = yRef.mWidth;
    return *this;
}

Rect Rect::operator*(float32 constant) const
{
    Rect temp;
    temp.mLeftTop = mLeftTop * constant;
    temp.mRightBottom = mRightBottom * constant;
    temp.mWidth = temp.mRightBottom.x - temp.mLeftTop.x;
    temp.mHeight = temp.mRightBottom.y - temp.mLeftTop.y;
    return temp;
}

Rect Rect::operator/(float32 constant) const
{
    Rect temp;
    temp.mLeftTop = mLeftTop / constant;
    temp.mRightBottom = mRightBottom / constant;
    temp.mWidth = temp.mRightBottom.x - temp.mLeftTop.x;
    temp.mHeight = temp.mRightBottom.y - temp.mLeftTop.y;

    return temp;
}

Rect& Rect::operator*=(float32 constant)
{
    mLeftTop *= constant;
    mRightBottom *= constant;
    mWidth = mRightBottom.x - mLeftTop.x;
    mHeight = mRightBottom.y - mLeftTop.y;
    return *this;
}

float32 Rect::getWidth() const
{
    return mWidth;
}

float32 Rect::getHeight() const
{
    return mHeight;
}

const Vec2& Rect::getLeftTop() const
{
    return mLeftTop;
}

const Vec2& Rect::getRightBottom() const
{
    return mRightBottom;
}

Vec2 Rect::getCenterPoint() const
{
    Vec2 centerPos;
    centerPos.x = (mLeftTop.x + mRightBottom.x) / 2.0f;
    centerPos.y = (mLeftTop.y + mRightBottom.y) / 2.0f;
    return centerPos;
}

void Rect::setPoints(const Vec2& leftTop, const Vec2& rightBottom)
{
    mLeftTop = leftTop;
    mRightBottom = rightBottom;
    mWidth = rightBottom.x - mLeftTop.x;
    mHeight = rightBottom.y - mLeftTop.y;
}

void Rect::setLeftTop(const Vec2& pos)
{
    mLeftTop = pos;
}

void Rect::setRightBottom(const Vec2& pos)
{
    mRightBottom = pos;
}
