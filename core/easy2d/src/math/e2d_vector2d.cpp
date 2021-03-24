#include "e2d_vector2d.h"

/* Easy2D */
using namespace Easy2D;

/* VECTOR2D */
Vector2D Vector2D::ZERO;
Vector2D Vector2D::ONE(1, 1);
Vector2D Vector2D::NEGATIVE_ONE(-1, -1);
Vector2D Vector2D::MIN(FLT_MIN, FLT_MIN);
Vector2D Vector2D::MAX(FLT_MAX, FLT_MAX);

void Vector2D::normalize()
{
    float d = sqrt(x * x + y * y);
    x /= d;
    y /= d;
}

float Vector2D::length() const
{
    return sqrt(x * x + y * y);
}

Radian Vector2D::direction() const
{
    return Radian(std::atan2(y, x));
}

float Vector2D::cross(const Vector2D& vec) const
{
    return x * vec.y - y * vec.x;
}

float Vector2D::dot(const Vector2D& vec) const
{
    return x * vec.x + y * vec.y;
}

float Vector2D::distance(const Vector2D& vec) const
{
    float dx = (x - vec.x);
    float dy = (y - vec.y);
    return  sqrt(dx * dx + dy * dy);
}

float Vector2D::distancePow2(const Vector2D& vec) const
{
    float dx = (x - vec.x);
    float dy = (y - vec.y);
    return  dx * dx + dy * dy;
}

Vector2D Vector2D::axis(const Vector2D& vec) const
{
    return Vector2D(x - vec.x, -y + vec.y);
}

Vector2D Vector2D::getNormalize() const
{
    float d = sqrt(x * x + y * y);
    return Vector2D(x / d, y / d);
}

Vector2D Vector2D::projected(const Vector2D& axis) const
{
    float p = ((x * axis.x + y * axis.y) / (axis.x * axis.x + axis.y * axis.y));
    return Vector2D(p * axis.x, p * axis.y);
}

String Vector2D::toString(const String& start, const String& sep, const String& end) const
{
    return start + std::to_string(x) + sep + std::to_string(y) + end;
}
