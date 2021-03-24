#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "e2d_vector2d.h"

namespace Easy2D
{
    class Vector3D
    {
    public:
        //-----------------------------------------------
        static Vector3D ZERO;
        static Vector3D ONE;
        static Vector3D MIN;
        static Vector3D MAX;
        static Vector3D NEGATIVE_ONE;
        //-----------------------------------------------
        union
        {
            struct { float x, y, z; };
            struct { float r, g, b; };
        };
        //-----------------------------------------------
        Vector3D() :x(0), y(0), z(0) {};
        Vector3D(const Vector2D& v, float z) :x(v.x), y(v.y), z(z) {};
        Vector3D(float x, const Vector2D& v) :x(x), y(v.x), z(v.y) {};
        Vector3D(float x, float y, float z) :x(x), y(y), z(z) {};
        ~Vector3D() {};
        //-----------------------------------------------
        inline Vec2 xy() const
        {
            return Vec2(x, y);
        }
        inline Vec2& xy()
        {
            return *((Vec2*)&x);
        }
        inline Vec2 rg() const
        {
            return Vec2(x, y);
        }
        inline Vec2& rg()
        {
            return *((Vec2*)&x);
        }
        //-----------------------------------------------
        template <char A>
        inline float to() const
        {
            switch (A)
            {
            case 'x':
            case 'r':
                return x;
            case 'y':
            case 'g':
                return y;
            case 'z':
            case 'b':
                return z;
            case 1://Math::nx:
                return -x;
            case 2://Math::ny:
                return -y;
            case 3://Math::nz:
                return -z;
            default:
                return 0.0;
                break;
            }
        }
        template <uchar X, uchar Y>
        inline Vec2 to() const
        {
            return Vec2(to<X>(), to<Y>());
        }
        template <uchar X, uchar Y, uchar Z>
        inline Vector3D to() const
        {
            return Vector3D(to<X>(), to<Y>(), to<Z>());
        }
        //-----------------------------------------------
        void normalize();
        //-----------------------------------------------
        float length() const;
        float dot(const Vector3D& vec) const;
        float distance(const Vector3D& vec) const;
        float distancePow2(const Vector3D& vec) const;
        Vector3D cross(const Vector3D& vec) const;
        Vector3D getNormalize() const;
        void orthoNormalize(Vector3D& b)
        {
            this->normalize();
            b -= b.projectToNormal(*this);
            b.normalize();
        }
        Vector3D projectToNormal(const Vector3D& direction)
        {
            return direction * dot(direction);
        }
        //-----------------------------------------------
        inline float squaredLength() const
        {
            return x * x + y * y + z * z;
        };
        inline void abs()
        {
            x = std::abs(x);
            y = std::abs(y);
            z = std::abs(z);
        }
        inline Vector3D getAbs() const
        {
            return Vector3D(std::abs(x), std::abs(y), std::abs(z));
        }
        //-----------------------------------------------
        inline float& operator [] (unsigned int i)
        {
            return i == 0 ? x : i == 1 ? y : z;
        }
        inline bool operator==(const Vector3D& v) const
        {
            return (x == v.x && y == v.y && z == v.z);
        }
        inline bool operator!=(const Vector3D& v) const
        {
            return (x != v.x || y != v.y || z != v.z);
        }
        //-----------------------------------------------
        inline Vector3D operator+(const Vector3D& v) const
        {
            return Vector3D(x + v.x, y + v.y, z + v.z);
        }
        inline Vector3D operator+(float v) const
        {
            return Vector3D(x + v, y + v, z + v);
        }

        inline Vector3D operator-(const Vector3D& v) const
        {
            return Vector3D(x - v.x, y - v.y, z - v.z);
        }
        inline Vector3D operator-(float v) const
        {
            return Vector3D(x - v, y - v, z - v);
        }
        inline Vector3D operator-(void) const
        {
            return Vector3D(-x, -y, -z);
        }
        inline Vector3D operator*(const Vector3D& v) const
        {
            return Vector3D(x * v.x, y * v.y, z * v.z);
        }
        inline Vector3D operator*(float v) const
        {
            return Vector3D(x * v, y * v, z * v);
        }
        inline Vector3D operator/(const Vector3D& v) const
        {
            return Vector3D(x / v.x, y / v.y, z / v.z);
        }
        inline Vector3D operator/(float v) const
        {
            return Vector3D(x / v, y / v, z / v);
        }
        //-----------------------------------------------
        inline const Vector3D& operator+=(const Vector3D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }
        inline const Vector3D& operator+=(const float& v)
        {
            x += v;
            y += v;
            z += v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector3D& operator-=(const Vector3D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }
        inline const Vector3D& operator-=(const float& v)
        {
            x -= v;
            y -= v;
            z -= v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector3D& operator*=(const Vector3D& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            return *this;
        }
        inline const Vector3D& operator*=(const float& v)
        {
            x *= v;
            y *= v;
            z *= v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector3D& operator/=(const Vector3D& v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            return *this;
        }
        inline const Vector3D& operator/=(const float& v)
        {
            x /= v;
            y /= v;
            z /= v;
            return *this;
        }
        //-----------------------------------------------
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
    inline Vector3D operator+(T v, const Vector3D& vt)
    {
        return Vector3D(v + vt.x, v + vt.y, v + vt.z);
    }
    template <typename T>
    inline Vector3D operator-(T v, const Vector3D& vt)
    {
        return Vector3D(v - vt.x, v - vt.y, v - vt.z);
    }
    template <typename T>
    inline Vector3D operator*(T v, const Vector3D& vt)
    {
        return Vector3D(v * vt.x, v * vt.y, v * vt.z);
    }
    template <typename T>
    inline Vector3D operator/(T v, const Vector3D& vt)
    {
        return Vector3D(v / vt.x, v / vt.y, v / vt.z);
    }

    //typedef
    //-----------------------------------------------
    typedef Vector3D Vec3;
}

#endif
