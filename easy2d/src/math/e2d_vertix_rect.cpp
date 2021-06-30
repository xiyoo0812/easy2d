#include "e2d_vertix_rect.h"
#include "e2d_math.h"

using namespace Easy2D;

VertixRect::VertixRect(const Vec2& bl, const Vec2& size)
    : mTL(bl.x, bl.y + size.y, 0, 1), mTR(bl.x + size.x, bl.y + size.y, 0, 1), mBL(bl.x, bl.y, 0, 1), mBR(bl.x + size.x, bl.y, 0, 1)
    , mSize(size)
{
}

VertixRect::VertixRect(const Vec4& tl, const Vec4& tr, const Vec4& bl, const Vec4& br)
    : mTL(tl), mTR(tr), mBL(bl), mBR(br)
{
    mSize.x = sqrt((tr.x - tl.x) * (tr.x - tl.x) + (tr.y - tl.y) * (tr.y - tl.y));
    mSize.y = sqrt((bl.x - tl.x) * (bl.x - tl.x) + (bl.y - tl.y) * (bl.y - tl.y));
}


VertixRect VertixRect::operator=(const VertixRect& yRef)
{
    mTL = yRef.mTL;
    mTR = yRef.mTR;
    mBL = yRef.mBL;
    mBR = yRef.mBR;
    mSize = yRef.mSize;
    return *this;
}

void VertixRect::mul(const Mat4& mat)
{
    Easy2D::mul(mTL, mat, mTL);
    Easy2D::mul(mTR, mat, mTR);
    Easy2D::mul(mBL, mat, mBL);
    Easy2D::mul(mBR, mat, mBR);
}

float32 VertixRect::getWidth() const
{
    return mSize.x;
}

float32 VertixRect::getHeight() const
{
    return mSize.y;
}

const Vec2& VertixRect::getSize() const
{
    return mSize;
}

const Vec4& VertixRect::getTopLeft() const
{
    return mTL;
}

const Vec4& VertixRect::getTopRight() const
{
    return mTR;
}

const Vec4& VertixRect::getBottomLeft() const
{
    return mBL;
}

const Vec4& VertixRect::getBottomRight() const
{
    return mBR;
}

bool VertixRect::posInRect(const Vec2& pos) const
{
#define cross(p1, p2, p) ((p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y))
    return cross(mTL, mTR, pos) * cross(mBR, mBL, pos) >= 0 && cross(mTR, mBR, pos) * cross(mBL, mTL, pos) >= 0;
}
