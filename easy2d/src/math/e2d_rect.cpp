#include "e2d_rect.h"
#include "e2d_math.h"

using namespace Easy2D;

Rect::Rect(const Vec2& leftTop, const Vec2& size)
    : mLeftTop(leftTop)
    , mSize(size)
{
}

Rect Rect::operator=(const Rect& yRef)
{
    mLeftTop = yRef.mLeftTop;
    mSize = yRef.mSize;
    return *this;
}

Rect Rect::operator*(float32 constant) const
{
    Rect temp;
    temp.mSize = mSize * constant;
    return temp;
}

Rect Rect::operator/(float32 constant) const
{
    Rect temp;
    temp.mSize = mSize / constant;
    return temp;
}

Rect& Rect::operator*=(float32 constant)
{
    mSize *= constant;
    return *this;
}

float32 Rect::getWidth() const
{
    return mSize.x;
}

float32 Rect::getHeight() const
{
    return mSize.y;
}

const Vec2& Rect::getLeftTop() const
{
    return mLeftTop;
}

Vec2 Rect::getCenterPoint() const
{
    Vec2 centerPos;
    centerPos.x = mLeftTop.x + mSize.x / 2.0f;
    centerPos.y = mLeftTop.y + mSize.y / 2.0f;
    return centerPos;
}

void Rect::setPoints(const Vec2& leftTop, const Vec2& rightBottom)
{
    mLeftTop = leftTop;
    mSize.x = rightBottom.x - mLeftTop.x;
    mSize.y = rightBottom.y - mLeftTop.y;
}

void Rect::setLeftTop(const Vec2& leftTop)
{
    mLeftTop = leftTop;
}

void Rect::setRightBottom(const Vec2& rightBottom)
{
    mSize.x = rightBottom.x - mLeftTop.x;
    mSize.y = rightBottom.y - mLeftTop.y;
}

bool Rect::posInRect(const Vec2& pos) const
{
    return Easy2D::posInRect(mLeftTop, mSize, pos);
}
