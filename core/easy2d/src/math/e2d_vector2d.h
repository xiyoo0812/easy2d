#ifndef VECTOR2D_H
#define VECTOR2D_H

#include "e2d_angel.h"

namespace Easy2D
{
    class Vector2D
    {
    public:
        union
        {
            struct { float x, y; };
            struct { float u, v; };
            struct { float r, g; };
        };
        //-----------------------------------------------
        static Vector2D ZERO;
        static Vector2D ONE;
        static Vector2D NEGATIVE_ONE;
        static Vector2D MIN;
        static Vector2D MAX;
        //-----------------------------------------------
        Vector2D() :x(0), y(0) {};
        Vector2D(float x, float y) :x(x), y(y) {};
        ~Vector2D() {};
        //-----------------------------------------------
        template <char A>
        inline float to() const
        {
            switch (A)
            {
            case 'x':
            case 'r':
            case 'u':
                return x;
            case 'y':
            case 'g':
            case 'v':
                return y;
            case 1://Math::nx:
                return -x;
            case 2://Math::ny:
                return -y;
            default:
                return 0.0;
                break;
            }
        }
        template <uchar X, uchar Y>
        inline Vector2D to() const
        {
            return Vector2D(to<X>(), to<Y>());
        }
        //-----------------------------------------------
        void normalize();
        //-----------------------------------------------
        float  length() const;
        Radian direction() const;
        float  cross(const Vector2D& vec) const;
        float  dot(const Vector2D& vec) const;
        float  distance(const Vector2D& vec) const;
        float  distancePow2(const Vector2D& vec) const;
        Vector2D axis(const Vector2D& vec) const;
        Vector2D getNormalize() const;
        Vector2D projected(const Vector2D& axis) const;
        //-----------------------------------------------
        inline float squaredLength() const
        {
            return x * x + y * y;
        };
        inline void abs()
        {
            x = std::abs(x);
            y = std::abs(y);
        }
        inline Vector2D getAbs() const
        {
            return Vector2D(std::abs(x), std::abs(y));
        }
        //-----------------------------------------------
        inline float& operator [] (unsigned int i)
        {
            return (i % 2 == 0) ? x : y;
        }
        inline bool operator==(const Vector2D& v) const
        {
            return (x == v.x && y == v.y);
        }
        inline bool operator!=(const Vector2D& v) const
        {
            return (x != v.x || y != v.y);
        }
        //-----------------------------------------------
        inline Vector2D operator+(const Vector2D& v) const
        {
            return Vector2D(x + v.x, y + v.y);
        }
        inline Vector2D operator+(float v) const
        {
            return Vector2D(x + v, y + v);
        }
        inline Vector2D operator-(const Vector2D& v) const
        {
            return Vector2D(x - v.x, y - v.y);
        }
        inline Vector2D operator-(float v) const
        {
            return Vector2D(x - v, y - v);
        }
        inline Vector2D operator-(void) const
        {
            return Vector2D(-x, -y);
        }
        inline Vector2D operator*(const Vector2D& v) const
        {
            return Vector2D(x * v.x, y * v.y);
        }
        inline Vector2D operator*(float v) const
        {
            return Vector2D(x * v, y * v);
        }
        inline Vector2D operator/(const Vector2D& v) const
        {
            return Vector2D(x / v.x, y / v.y);
        }
        inline Vector2D operator/(float v) const
        {
            return Vector2D(x / v, y / v);
        }
        //-----------------------------------------------
        inline const Vector2D& operator+=(const Vector2D& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }
        inline const Vector2D& operator+=(const float& v)
        {
            x += v;
            y += v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector2D& operator-=(const Vector2D& v)
        {
            x -= v.x;
            y -= v.y;
            return *this;
        }
        inline const Vector2D& operator-=(const float& v)
        {
            x -= v;
            y -= v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector2D& operator*=(const Vector2D& v)
        {
            x *= v.x;
            y *= v.y;
            return *this;
        }
        inline const Vector2D& operator*=(const float& v)
        {
            x *= v;
            y *= v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector2D& operator/=(const Vector2D& v)
        {
            x /= v.x;
            y /= v.y;
            return *this;
        }
        inline const Vector2D& operator/=(const float& v)
        {
            x /= v;
            y /= v;
            return *this;
        }
        //-----------------------------------------------
        //cast to pointer to float
        operator float* ()
        {
            return &this->x;
        }
        operator const float* () const
        {
            return &this->x;
        }
        //-----------------------------------------------
        String toString(const String& start = "(", const String& sep = " ", const String& end = ")\n") const;
    };

    template <typename T>
    inline Vector2D operator+(T v, const Vector2D& vt)
    {
        return Vector2D(v + vt.x, v + vt.y);
    }
    template <typename T>
    inline Vector2D operator-(T v, const Vector2D& vt)
    {
        return Vector2D(v - vt.x, v - vt.y);
    }
    template <typename T>
    inline Vector2D operator*(T v, const Vector2D& vt)
    {
        return Vector2D(v * vt.x, v * vt.y);
    }
    template <typename T>
    inline Vector2D operator/(T v, const Vector2D& vt)
    {
        return Vector2D(v / vt.x, v / vt.y);
    }

    //typedef
    //-----------------------------------------------
    typedef Vector2D Vec2;
}

#endif
