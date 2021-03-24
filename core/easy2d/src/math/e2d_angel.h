#ifndef ANGEL_H
#define ANGEL_H

#include "e2d_config.h"

namespace Easy2D
{
    class Degree;
    class Angle;

    class Radian
    {
        float rad;

    public:
        //-----------------------------------------------
        explicit Radian(float r = 0) : rad(r) {}
        Radian(const Degree& d);
        //-----------------------------------------------
        Radian& operator = (const float& f) { rad = f; return *this; }
        Radian& operator = (const Radian& r) { rad = r.rad; return *this; }
        Radian& operator = (const Degree& d);
        Radian& operator = (const Angle& a);
        //-----------------------------------------------
        float valueDegrees() const;
        float valueRadians() const { return rad; }
        //-----------------------------------------------
        float cos() const;
        float sin() const;
        //-----------------------------------------------
        const Radian& operator + () const { return *this; }
        Radian operator + (const Radian& r) const { return Radian(rad + r.rad); }
        Radian operator + (const Degree& d) const;
        Radian& operator += (const Radian& r) { rad += r.rad; return *this; }
        Radian& operator += (const Degree& d);
        Radian operator - () const { return Radian(-rad); }
        Radian operator - (const Radian& r) const { return Radian(rad - r.rad); }
        Radian operator - (const Degree& d) const;
        Radian& operator -= (const Radian& r) { rad -= r.rad; return *this; }
        Radian& operator -= (const Degree& d);
        Radian operator * (float f) const { return Radian(rad * f); }
        Radian operator * (const Radian& f) const { return Radian(rad * f.rad); }
        Radian& operator *= (float f) { rad *= f; return *this; }
        Radian operator / (float f) const { return Radian(rad / f); }
        Radian& operator /= (float f) { rad /= f; return *this; }

        bool operator <  (const Radian& r) const { return rad < r.rad; }
        bool operator <= (const Radian& r) const { return rad <= r.rad; }
        bool operator == (const Radian& r) const { return rad == r.rad; }
        bool operator != (const Radian& r) const { return rad != r.rad; }
        bool operator >= (const Radian& r) const { return rad >= r.rad; }
        bool operator >  (const Radian& r) const { return rad > r.rad; }
        //-----------------------------------------------
        String toString(const String& start = "Radian(", const String& end = ")\n") const
        {
            return start + std::to_string(rad) + end;
        }
    };

    class Degree
    {
        float deg;

    public:
        //-----------------------------------------------
        explicit Degree(float d = 0) : deg(d) {}
        Degree(const Radian& r) : deg(r.valueDegrees()) {}
        //-----------------------------------------------
        Degree& operator = (const float& f) { deg = f; return *this; }
        Degree& operator = (const Degree& d) { deg = d.deg; return *this; }
        Degree& operator = (const Radian& r) { deg = r.valueDegrees(); return *this; }
        Degree& operator = (const Angle& a);
        //-----------------------------------------------
        float valueDegrees() const { return deg; }
        float valueRadians() const;
        //-----------------------------------------------
        float cos() const;
        float sin() const;
        //-----------------------------------------------
        const Degree& operator + () const { return *this; }
        Degree operator + (const Degree& d) const { return Degree(deg + d.deg); }
        Degree operator + (const Radian& r) const { return Degree(deg + r.valueDegrees()); }
        Degree& operator += (const Degree& d) { deg += d.deg; return *this; }
        Degree& operator += (const Radian& r) { deg += r.valueDegrees(); return *this; }
        Degree operator - () const { return Degree(-deg); }
        Degree operator - (const Degree& d) const { return Degree(deg - d.deg); }
        Degree operator - (const Radian& r) const { return Degree(deg - r.valueDegrees()); }
        Degree& operator -= (const Degree& d) { deg -= d.deg; return *this; }
        Degree& operator -= (const Radian& r) { deg -= r.valueDegrees(); return *this; }
        Degree operator * (float f) const { return Degree(deg * f); }
        Degree operator * (const Degree& f) const { return Degree(deg * f.deg); }
        Degree& operator *= (float f) { deg *= f; return *this; }
        Degree operator / (float f) const { return Degree(deg / f); }
        Degree& operator /= (float f) { deg /= f; return *this; }

        bool operator <  (const Degree& d) const { return deg < d.deg; }
        bool operator <= (const Degree& d) const { return deg <= d.deg; }
        bool operator == (const Degree& d) const { return deg == d.deg; }
        bool operator != (const Degree& d) const { return deg != d.deg; }
        bool operator >= (const Degree& d) const { return deg >= d.deg; }
        bool operator >  (const Degree& d) const { return deg > d.deg; }
        //-----------------------------------------------
        String toString(const String& start = "Degree(", const String& end = ")\n") const
        {
            return start + std::to_string(deg) + end;
        }
    };

    class Angle
    {
        Radian angle;

    public:
        enum InitType
        {
            RADIAN,
            DEGREE
        };

        Angle() {}
        Angle(float value, InitType type)
        {
            switch (type)
            {
            case RADIAN: angle = Radian(value); break;
            case DEGREE: angle = Degree(value); break;
                //default: DEBUG_ASSERT_MSG(0,"Type of angle not valid"); break;
            }
        }
        Angle(const Angle& a) : angle(a.angle) {}
        Angle(const Radian& r) : angle(r) {}
        Angle(const Degree& r) : angle(r.valueRadians()) {}
        //-----------------------------------------------
        static Angle radian(float r)
        {
            return Angle(Radian(r));
        }
        static Angle degree(float d)
        {
            return Angle(Degree(d));
        }
        //-----------------------------------------------
        operator Radian() const
        {
            return angle;
        }
        operator Degree() const
        {
            return Degree(angle);
        }
        //-----------------------------------------------
        float cos() const;
        float sin() const;
        //-----------------------------------------------
        float valueDegrees() const
        {
            return angle.valueDegrees();
        }
        float valueRadians() const
        {
            return angle.valueRadians();
        }
        //-----------------------------------------------
        const Angle& operator + () const { return *this; }
        Angle operator   +  (const Angle& r) const { return Angle(angle + r.angle); }
        Angle& operator +=  (const Angle& r) { angle += r.angle; return *this; }
        Angle operator   -  () const { return Angle(-angle); }
        Angle operator   -  (const Angle& r) const { return Angle(angle - r.angle); }
        Angle& operator -=  (const Angle& r) { angle -= r.angle; return *this; }
        Angle operator   *  (float f) const { return Angle(angle * f); }
        Angle operator   *  (const Angle& f) const { return Angle(Radian(angle * f.angle)); }
        Angle& operator *=  (float f) { angle *= f; return *this; }
        Angle operator   /  (float f) const { return Angle(Radian(angle / f)); }
        Angle& operator  /= (float f) { angle /= f; return *this; }

        bool operator <  (const Angle& r) const { return angle < r.angle; }
        bool operator <= (const Angle& r) const { return angle <= r.angle; }
        bool operator == (const Angle& r) const { return angle == r.angle; }
        bool operator != (const Angle& r) const { return angle != r.angle; }
        bool operator >= (const Angle& r) const { return angle >= r.angle; }
        bool operator >  (const Angle& r) const { return angle > r.angle; }
        //-----------------------------------------------
    };

    //-----------------------------------------------
    inline Angle operator * (float a, const Angle& b)
    {
        return Angle(Radian(a * b.valueRadians()));
    }
    inline Angle operator / (float a, const Angle& b)
    {
        return Angle(Radian(a / b.valueRadians()));
    }

    inline Radian operator * (float a, const Radian& b)
    {
        return Radian(a * b.valueRadians());
    }
    inline Radian operator / (float a, const Radian& b)
    {
        return Radian(a / b.valueRadians());
    }

    inline Degree operator * (float a, const Degree& b)
    {
        return Degree(a * b.valueDegrees());
    }
    inline Radian operator / (float a, const Degree& b)
    {
        return Degree(a / b.valueDegrees());
    }
}

#endif
