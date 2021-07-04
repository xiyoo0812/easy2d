#include "e2d_vertix_rect.h"
#include "e2d_math.h"

using namespace Easy2D;

VertixRect::VertixRect(const Vec2& bl, const Vec2& size) : mSize(size)
{
    mVectics =
    {
        Vec4(bl.x, bl.y + size.y, 0, 1),
        Vec4(bl.x + size.x, bl.y + size.y, 0, 1),
        Vec4(bl.x, bl.y, 0, 1),
        Vec4(bl.x + size.x, bl.y, 0, 1)
    };
}

VertixRect::VertixRect(const Vec4& tl, const Vec4& tr, const Vec4& bl, const Vec4& br)
{
    mVectics = { tl, tr, bl, br };
    mSize.x = sqrt((tr.x - tl.x) * (tr.x - tl.x) + (tr.y - tl.y) * (tr.y - tl.y));
    mSize.y = sqrt((bl.x - tl.x) * (bl.x - tl.x) + (bl.y - tl.y) * (bl.y - tl.y));
}

VertixRect VertixRect::operator=(const VertixRect& yRef)
{
    mVectics = yRef.mVectics;
    mSize = yRef.mSize;
    return *this;
}

void VertixRect::buildRect(const Vec2& bl, const Vec2& size, const Mat4& mat)
{
    Vec2 scale;
    Easy2D::getScaling(mat, scale);
    mSize = size * scale;
    mVectics =
    {
        Easy2D::mul(Vec4(bl.x, bl.y + size.y, 0, 1), mat),
        Easy2D::mul(Vec4(bl.x + size.x, bl.y + size.y, 0, 1), mat),
        Easy2D::mul(Vec4(bl.x, bl.y, 0, 1), mat),
        Easy2D::mul(Vec4(bl.x + size.x, bl.y, 0, 1), mat)
    };
}

Vec2 VertixRect::pos2Ratio(const Vec2& pos) const
{
    float32 y = Easy2D::distanceLine(Vec2(mVectics[0]), Vec2(mVectics[1]), pos);
    float32 x = Easy2D::distanceLine(Vec2(mVectics[0]), Vec2(mVectics[2]), pos);
    return Vec2(x / mSize.x, y / mSize.y);
}

void VertixRect::mul(const Mat4& mat)
{
    Vec2 scale;
    Easy2D::getScaling(mat, scale);
    Easy2D::mul(mVectics[0], mat, mVectics[0]);
    Easy2D::mul(mVectics[1], mat, mVectics[1]);
    Easy2D::mul(mVectics[2], mat, mVectics[2]);
    Easy2D::mul(mVectics[3], mat, mVectics[3]);
    mSize *= scale;
}

float32 VertixRect::getWidth() const
{
    return mSize.x;
}

float32 VertixRect::getHeight() const
{
    return mSize.y;
}

const Vec4& VertixRect::getTopLeft() const
{
    return mVectics[0];
}

const Vec4& VertixRect::getTopRight() const
{
    return mVectics[1];
}

const Vec4& VertixRect::getBottomLeft() const
{
    return mVectics[2];
}

const Vec4& VertixRect::getBottomRight() const
{
    return mVectics[3];
}

bool VertixRect::posInRect(const Vec2& pos) const
{
#define cross(p1, p2, p) ((p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y))
    return cross(mVectics[0], mVectics[1], pos) * cross(mVectics[3], mVectics[2], pos) >= 0 && cross(mVectics[1], mVectics[3], pos) * cross(mVectics[2], mVectics[0], pos) >= 0;
}
