#include "e2d_vertex_rect.h"
#include "e2d_math.h"

using namespace Easy2D;

VertexRect::VertexRect(const Vec2& bl, const Vec2& size) : mSize(size)
{
    mVertexs =
    {
        Vec4(bl.x, bl.y + size.y, 0, 1),
        Vec4(bl.x + size.x, bl.y + size.y, 0, 1),
        Vec4(bl.x, bl.y, 0, 1),
        Vec4(bl.x + size.x, bl.y, 0, 1)
    };
}

VertexRect::VertexRect(const Vec4& tl, const Vec4& tr, const Vec4& bl, const Vec4& br)
{
    mVertexs = { tl, tr, bl, br };
    mSize.x = Easy2D::distance(tl, tr);
    mSize.y = Easy2D::distance(tl, bl);
}

VertexRect VertexRect::operator=(const VertexRect& yRef)
{
    mVertexs = yRef.mVertexs;
    mSize = yRef.mSize;
    return *this;
}

void VertexRect::general(const Vec2& bl, const Vec2& size, const Mat4& mat)
{
    Vec2 scale;
    Easy2D::getScaling(mat, scale);
    mSize = size * scale;
    mVertexs =
    {
        Easy2D::mul(Vec4(bl.x, bl.y + size.y, 0, 1), mat),
        Easy2D::mul(Vec4(bl.x + size.x, bl.y + size.y, 0, 1), mat),
        Easy2D::mul(Vec4(bl.x, bl.y, 0, 1), mat),
        Easy2D::mul(Vec4(bl.x + size.x, bl.y, 0, 1), mat)
    };
}

Vec2 VertexRect::pos2Ratio(const Vec2& pos) const
{
    Vec2 dy = Easy2D::distanceLine(Vec2(mVertexs[0]), Vec2(mVertexs[1]), pos);
    Vec2 dx = Easy2D::distanceLine(Vec2(mVertexs[0]), Vec2(mVertexs[2]), pos);
    float32 x = (dy.y >= 1) ? 1 : ((dy.y <= 0) ? 0 : dx.x / mSize.x);
    float32 y = (dx.y >= 1) ? 1 : ((dx.y <= 0) ? 0 : dy.x / mSize.y);
    return Vec2(x, y);
}

void VertexRect::transform(const Mat4& mat)
{
    Vec2 scale;
    Easy2D::getScaling(mat, scale);
    Easy2D::mul(mVertexs[0], mat, mVertexs[0]);
    Easy2D::mul(mVertexs[1], mat, mVertexs[1]);
    Easy2D::mul(mVertexs[2], mat, mVertexs[2]);
    Easy2D::mul(mVertexs[3], mat, mVertexs[3]);
    mSize *= scale;
}

float32 VertexRect::getWidth() const
{
    return mSize.x;
}

float32 VertexRect::getHeight() const
{
    return mSize.y;
}

const Vec4& VertexRect::getTopLeft() const
{
    return mVertexs[0];
}

const Vec4& VertexRect::getTopRight() const
{
    return mVertexs[1];
}

const Vec4& VertexRect::getBottomLeft() const
{
    return mVertexs[2];
}

const Vec4& VertexRect::getBottomRight() const
{
    return mVertexs[3];
}

bool VertexRect::posInRect(const Vec2& pos) const
{
#define cross(p1, p2, p) ((p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y))
    return cross(mVertexs[0], mVertexs[1], pos) * cross(mVertexs[3], mVertexs[2], pos) >= 0 && cross(mVertexs[1], mVertexs[3], pos) * cross(mVertexs[2], mVertexs[0], pos) >= 0;
}
