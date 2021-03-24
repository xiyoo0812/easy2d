#include "e2d_vector4d.h"

/* Easy2D */
using namespace Easy2D;

/* VECTOR4D */
Vector4D Vector4D::ZERO;
Vector4D Vector4D::ONE(1, 1, 1, 1);
Vector4D Vector4D::NEGATIVE_ONE(-1, -1, -1, -1);
Vector4D Vector4D::MIN(FLT_MIN, FLT_MIN, FLT_MIN, FLT_MIN);
Vector4D Vector4D::MAX(FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX);

void Vector4D::normalize()
{
    float d = sqrt(x * x + y * y + z * z + w * w);
    x /= d;
    y /= d;
    z /= d;
    w /= d;
}

float Vector4D::length() const
{
    return sqrt(x * x + y * y + z * z + w * w);
}

float Vector4D::dot(const Vector4D& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

float Vector4D::distance(const Vector4D& vec) const
{
    float dx = x - vec.x, dy = y - vec.y, dz = z - vec.z, dw = w - vec.w;
    return sqrt(dx * dx + dy * dy + dz * dz + dw * dw);
}

float Vector4D::distancePow2(const Vector4D& vec) const
{
    float dx = x - vec.x, dy = y - vec.y, dz = z - vec.z, dw = w - vec.w;
    return dx * dx + dy * dy + dz * dz + dw * dw;
}

Vector4D Vector4D::getNormalize() const
{
    float d = sqrt(x * x + y * y + z * z + w * w);
    return Vector4D(x / d, y / d, z / d, w / d);
}

String Vector4D::toString(const String& start, const String& sep, const String& end) const
{
    return start + std::to_string(x) + sep + std::to_string(y) + sep + std::to_string(z) + sep + std::to_string(w) + end;
}
