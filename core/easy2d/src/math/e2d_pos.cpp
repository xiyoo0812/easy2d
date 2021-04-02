#include "e2d_pos.h"

using namespace Easy2D;

Pos::Pos()
{

}

Pos::Pos(const Vec2& vec, lay layer)
    : x(vec.x), y(vec.y), l(layer)
{

}

Pos::Pos(int32 X, int32 Y, lay layer)
    : x(float32(X)), y(float32(Y)), l(layer)
{

}

Pos::Pos(int64 X, int64 Y, lay layer)
    : x(float32(X)), y(float32(Y)), l(layer)
{

}

Pos::Pos(float32 X, float32 Y, lay layer)
    : x(X), y(Y), l(layer)
{

}

Pos::Pos(float64 X, float64 Y, lay layer)
    : x(float32(X)), y(float32(Y)), l(layer)
{

}

Pos::Pos(const Pos& yRef)
    : x(yRef.x), y(yRef.y), l(yRef.l)
{
}

Pos::Pos(Pos&& yRef)
    : x(std::move(yRef.x)), y(std::move(yRef.y)), l(std::move(yRef.l))
{

}

bool Pos::operator==(const Pos& yRef) const
{
    return (x == yRef.x && y == yRef.y && l == yRef.l);
}

bool Pos::operator==(const Vec2& yRef) const
{
    return (x == yRef.x && y == yRef.y);
}

bool Pos::operator!=(const Pos& yRef) const
{
    return !(*this == yRef);
}

bool Pos::operator!=(const Vec2& yRef) const
{
    return !(*this == yRef);
}

Pos& Pos::operator=(const Pos& yRef)
{
    x = yRef.x;
    y = yRef.y;
    l = yRef.l;
    return *this;
}

Pos& Pos::operator=(Pos&& yRef)
{
    x = std::move(yRef.x);
    y = std::move(yRef.y);
    l = std::move(yRef.l);
    return *this;
}

Pos& Pos::operator=(const Vec2& yRef)
{
    x = yRef.x;
    y = yRef.y;
    return *this;
}

Pos& Pos::operator+=(const Pos& yRef)
{
    x += yRef.x;
    y += yRef.y;
    return *this;
}

Pos& Pos::operator+=(const Vec2& yRef)
{
    x += yRef.x;
    y += yRef.y;
    return *this;
}

Pos& Pos::operator-=(const Pos& yRef)
{
    x -= yRef.x;
    y -= yRef.y;
    return *this;
}

Pos& Pos::operator-=(const Vec2& yRef)
{
    x -= yRef.x;
    y -= yRef.y;
    return *this;
}

Pos Pos::operator+(const Pos& yRef) const
{
    Pos copy(*this);
    copy.x += yRef.x;
    copy.y += yRef.y;
    return copy;
}

Pos Pos::operator+(const Vec2& yRef) const
{
    Pos copy(*this);
    copy.x += yRef.x;
    copy.y += yRef.y;
    return copy;
}

Pos Pos::operator-(const Pos& yRef) const
{
    Pos copy(*this);
    copy.x -= yRef.x;
    copy.y -= yRef.y;
    return copy;
}

Pos Pos::operator-(const Vec2& yRef) const
{
    Pos copy(*this);
    copy.x -= yRef.x;
    copy.y -= yRef.y;
    return copy;
}

Pos Pos::operator*(uint32 n)
{
    Pos copy(*this);
    copy *= n;
    return copy;
}

Pos Pos::operator*(uint64 n)
{
    Pos copy(*this);
    copy *= n;
    return copy;
}

Pos Pos::operator*(int32 n)
{
    Pos copy(*this);
    copy *= n;
    return copy;
}

Pos Pos::operator*(int64 n)
{
    Pos copy(*this);
    copy *= n;
    return copy;
}

Pos Pos::operator*(float32 n)
{
    Pos copy(*this);
    copy *= n;
    return copy;
}

Pos Pos::operator*(float64 n)
{
    Pos copy(*this);
    copy *= n;
    return copy;
}

Pos Pos::operator/(uint32 n)
{
    Pos copy(*this);
    copy /= n;
    return copy;
}

Pos Pos::operator/(uint64 n)
{
    Pos copy(*this);
    copy /= n;
    return copy;
}

Pos Pos::operator/(int32 n)
{
    Pos copy(*this);
    copy /= n;
    return copy;
}

Pos Pos::operator/(int64 n)
{
    Pos copy(*this);
    copy /= n;
    return copy;
}

Pos Pos::operator/(float32 n)
{
    Pos copy(*this);
    copy /= n;
    return copy;
}

Pos Pos::operator/(float64 n)
{
    Pos copy(*this);
    copy /= n;
    return copy;
}

Pos& Pos::operator*=(uint32 n)
{
    x *= float32(n);
    y *= float32(n);
    return *this;
}

Pos& Pos::operator*=(uint64 n)
{
    x *= float32(n);
    y *= float32(n);
    return *this;
}

Pos& Pos::operator*=(int32 n)
{
    x *= float32(n);
    y *= float32(n);
    return *this;
}

Pos& Pos::operator*=(int64 n)
{
    x *= float32(n);
    y *= float32(n);
    return *this;
}

Pos& Pos::operator*=(float32 n)
{
    x *= n;
    y *= n;
    return *this;
}

Pos& Pos::operator*=(float64 n)
{
    x *= float32(n);
    y *= float32(n);
    return *this;
}

Pos& Pos::operator/=(uint32 n)
{
    x /= float32(n);
    y /= float32(n);
    return *this;
}

Pos& Pos::operator/=(uint64 n)
{
    x /= float32(n);
    y /= float32(n);
    return *this;
}

Pos& Pos::operator/=(int32 n)
{
    x /= float32(n);
    y /= float32(n);
    return *this;
}

Pos& Pos::operator/=(int64 n)
{
    x /= float32(n);
    y /= float32(n);
    return *this;
}

Pos& Pos::operator/=(float32 n)
{
    x /= n;
    y /= n;
    return *this;
}

Pos& Pos::operator/=(float64 n)
{
    x /= float32(n);
    y /= float32(n);
    return *this;
}

Pos operator*(uint32 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= float32(n);
    copy.y *= float32(n);
    return copy;
}

Pos operator*(uint64 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= float32(n);
    copy.y *= float32(n);
    return copy;
}

Pos operator*(int32 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= float32(n);
    copy.y *= float32(n);
    return copy;
}

Pos operator*(int64 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= float32(n);
    copy.y *= float32(n);
    return copy;
}

Pos operator*(float32 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= n;
    copy.y *= n;
    return copy;
}

Pos operator*(float64 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= float32(n);
    copy.y *= float32(n);
    return copy;
}

Pos operator*(const Vec2& v, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x *= v.x;
    copy.y *= v.y;
    return copy;
}

Pos operator/(uint32 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= float32(n);
    copy.y /= float32(n);
    return copy;
}

Pos operator/(uint64 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= float32(n);
    copy.y /= float32(n);
    return copy;
}

Pos operator/(int32 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= float32(n);
    copy.y /= float32(n);
    return copy;
}

Pos operator/(int64 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= float32(n);
    copy.y /= float32(n);
    return copy;
}

Pos operator/(float32 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= n;
    copy.y /= n;
    return copy;
}

Pos operator/(float64 n, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= float32(n);
    copy.y /= float32(n);
    return copy;
}

Pos operator/(const Vec2& v, const Pos& yRef)
{
    Pos copy(yRef);
    copy.x /= v.x;
    copy.y /= v.y;
    return copy;
}

bool operator==(const Vec2& lRef, const Pos& rRef)
{
    return rRef == lRef;
}

bool operator!=(const Vec2& lRef, const Pos& rRef)
{
    return rRef == lRef;
}

Vec2 Pos::pos2D() const
{
    return Vec2(x, y);
}

Vec3 Pos::pos3D() const
{
    return Vec3(x, y, float32(l));
}

float32 Pos::length() const
{
    return sqrt(pow(x, 2) + pow(y, 2));
}
