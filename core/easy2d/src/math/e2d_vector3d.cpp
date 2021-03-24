#include "e2d_vector3d.h"

/* Easy2D */
using namespace Easy2D;

/* VECTOR3D */
Vector3D Vector3D::ZERO;
Vector3D Vector3D::ONE(1, 1, 1);
Vector3D Vector3D::NEGATIVE_ONE(-1, -1, -1);
Vector3D Vector3D::MIN(FLT_MIN, FLT_MIN, FLT_MIN);
Vector3D Vector3D::MAX(FLT_MAX, FLT_MAX, FLT_MAX);

void Vector3D::normalize()
{
    float d = sqrt(x * x + y * y + z * z);
    x /= d;
    y /= d;
    z /= d;
}

float Vector3D::length() const
{
    return sqrt(x * x + y * y + z * z);
}

float Vector3D::dot(const Vector3D& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}

float Vector3D::distance(const Vector3D& vec) const
{
    float dx = x - vec.x, dy = y - vec.y, dz = z - vec.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

float Vector3D::distancePow2(const Vector3D& vec) const
{
    float dx = x - vec.x, dy = y - vec.y, dz = z - vec.z;
    return dx * dx + dy * dy + dz * dz;
}

Vector3D Vector3D::cross(const Vector3D& vec) const
{
    return Vector3D(y * vec.z - z * vec.y,
        z * vec.x - x * vec.z,
        x * vec.y - y * vec.x);
}

Vector3D Vector3D::getNormalize() const
{
    float d = sqrt(x * x + y * y + z * z);
    return Vector3D(x / d, y / d, z / d);
}

String Vector3D::toString(const String& start, const String& sep, const String& end) const
{
    return start + std::to_string(x) + sep + std::to_string(y) + sep + std::to_string(z) + end;
}
