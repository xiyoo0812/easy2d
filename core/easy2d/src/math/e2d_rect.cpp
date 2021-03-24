#include "e2d_rect.h"

using namespace Easy2D;

Rect::Rect(const Vec2& leftBottom, const Vec2& rightBottom, const Vec2& leftTop, const Vec2& rightTop)
    : mLeftTop(leftTop)
    , mRightTop(rightTop)
    , mLeftBottom(leftBottom)
    , mRightBottom(rightBottom)
{
    mWidth = mRightTop.x - mLeftTop.x;
    mHeight = mRightTop.y - mLeftTop.y;
}

Rect Rect::operator=(const Rect& yRef)
{
    mHeight = yRef.mHeight;
    mLeftBottom = yRef.mLeftBottom;
    mLeftTop = yRef.mLeftTop;
    mRightBottom = yRef.mRightBottom;
    mRightTop = yRef.mRightTop;
    mWidth = yRef.mWidth;
    return *this;
}

Rect Rect::operator*(float32 constant) const
{
    Rect temp;
    temp.mLeftBottom = mLeftBottom * constant;
    temp.mLeftTop = mLeftTop * constant;
    temp.mRightBottom = mRightBottom * constant;
    temp.mRightTop = mRightTop * constant;
    temp.mWidth = temp.mRightTop.x - temp.mLeftTop.x;
    temp.mHeight = temp.mRightTop.y - temp.mLeftTop.y;
    return temp;
}

Rect Rect::operator/(float32 constant) const
{
    Rect temp;
    temp.mLeftBottom = mLeftBottom / constant;
    temp.mLeftTop = mLeftTop / constant;
    temp.mRightBottom = mRightBottom / constant;
    temp.mRightTop = mRightTop / constant;
    temp.mWidth = temp.mRightTop.x - temp.mLeftTop.x;
    temp.mHeight = temp.mRightTop.y - temp.mLeftTop.y;

    return temp;
}

Rect& Rect::operator*=(float32 constant)
{
    mLeftBottom *= constant;
    mLeftTop *= constant;
    mRightTop *= constant;
    mRightBottom *= constant;
    mWidth = mRightTop.x - mLeftTop.x;
    mHeight = mRightTop.y - mLeftTop.y;
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

const Vec2& Rect::getRightTop() const
{
    return mRightTop;
}

const Vec2& Rect::getRightBottom() const
{
    return mRightBottom;
}

const Vec2& Rect::getLeftBottom() const
{
    return mLeftBottom;
}

Vec2 Rect::getCenterPoint() const
{
    Vec2 centerPos;
    centerPos.x = (getRealLeft() + getRealRight()) / 2.0f;
    centerPos.y = (getRealTop() + getRealBottom()) / 2.0f;
    return centerPos;
}

float32 Rect::getRealLeft() const
{
    float32 realLeft(mLeftTop.x);
    realLeft = realLeft > mLeftBottom.x ? mLeftBottom.x : realLeft;
    realLeft = realLeft > mRightBottom.x ? mRightBottom.x : realLeft;
    realLeft = realLeft > mRightTop.x ? mRightTop.x : realLeft;
    return realLeft;
}

float32 Rect::getRealRight() const
{
    float32 realRight(mRightTop.x);
    realRight = realRight < mLeftBottom.x ? mLeftBottom.x : realRight;
    realRight = realRight < mRightBottom.x ? mRightBottom.x : realRight;
    realRight = realRight < mLeftTop.x ? mLeftTop.x : realRight;
    return realRight;
}

float32 Rect::getRealTop() const
{
    float32 realTop(mRightTop.y);
    realTop = realTop < mLeftBottom.y ? mLeftBottom.y : realTop;
    realTop = realTop < mRightBottom.y ? mRightBottom.y : realTop;
    realTop = realTop < mLeftTop.y ? mLeftTop.y : realTop;
    return realTop;
}

float32 Rect::getRealBottom() const
{
    float32 realBottom(mLeftBottom.y);
    realBottom = realBottom > mLeftTop.y ? mLeftTop.y : realBottom;
    realBottom = realBottom > mRightBottom.y ? mRightBottom.y : realBottom;
    realBottom = realBottom > mRightTop.y ? mRightTop.y : realBottom;
    return realBottom;
}

void Rect::setPoints(const Vec2& leftBottom, const Vec2& rightBottom, const Vec2& leftTop, const Vec2& rightTop)
{
    mLeftBottom = leftBottom;
    mLeftTop = leftTop;
    mRightBottom = rightBottom;
    mRightTop = rightTop;

    mWidth = mRightTop.x - mLeftTop.x;
    mHeight = mRightTop.y - mLeftTop.y;
}

void Rect::setLeftTop(const Vec2& pos)
{
    mLeftTop = pos;
}

void Rect::setLeftBottom(const Vec2& pos)
{
    mLeftBottom = pos;
}

void Rect::setRightTop(const Vec2& pos)
{
    mRightTop = pos;
}

void Rect::setRightBottom(const Vec2& pos)
{
    mRightBottom = pos;
}
