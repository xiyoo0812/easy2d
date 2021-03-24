#include "e2d_angel.h"
#include "e2d_math.h"

/* Easy2D */
using namespace Easy2D;

/* RADIAN */
Radian::Radian(const Degree& d)
    : rad(d.valueRadians())
{
}

Radian& Radian::operator = (const Degree& d)
{
    rad = d.valueRadians();
    return *this;
}

Radian& Radian::operator = (const Angle& a)
{
    rad = a.valueRadians();
    return *this;
}

Radian Radian::operator + (const Degree& d) const
{
    return Radian(rad + d.valueRadians());
}

Radian& Radian::operator += (const Degree& d)
{
    rad += d.valueRadians();
    return *this;
}

Radian Radian::operator - (const Degree& d) const
{
    return Radian(rad - d.valueRadians());
}

Radian& Radian::operator -= (const Degree& d)
{
    rad -= d.valueRadians();
    return *this;
}

float Radian::valueDegrees() const
{
    return Math::todeg(rad);
}

float Radian::cos() const
{
    return std::cos(rad);
}

float Radian::sin() const
{
    return std::sin(rad);
}

/* DEGREE */
Degree& Degree::operator = (const Angle& a)
{
    deg = a.valueDegrees();
    return *this;
}

float Degree::valueRadians() const
{
    return Math::torad(deg);
}

float Degree::cos() const
{
    return std::cos(Math::torad(deg));
}

float Degree::sin() const
{
    return std::sin(Math::torad(deg));
}

/* ANGLE */
float Angle::cos() const
{
    return std::cos(angle.valueRadians());
}

float Angle::sin() const
{
    return std::sin(angle.valueRadians());
}
