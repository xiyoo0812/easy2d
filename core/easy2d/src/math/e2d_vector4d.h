#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "e2d_vector3d.h"

namespace Easy2D
{
    class Vector4D
    {
    public:
        //-----------------------------------------------
        static Vector4D ZERO;
        static Vector4D ONE;
        static Vector4D MIN;
        static Vector4D MAX;
        static Vector4D NEGATIVE_ONE;
        //-----------------------------------------------
        union
        {
            struct { float x, y, z, w; };
            struct { float r, g, b, a; };
        };
        //-----------------------------------------------
        Vector4D() :x(0), y(0), z(0), w(0) {};
        Vector4D(float x, float y, float z, float w) :x(x), y(y), z(z), w(w) {};
        Vector4D(const Vector2D& v, float z, float w) :x(v.x), y(v.y), z(z), w(w) {};
        Vector4D(float x, const Vector2D& v, float w) :x(x), y(v.x), z(v.y), w(w) {};
        Vector4D(float x, float y, const Vector2D& v) :x(x), y(y), z(v.x), w(v.y) {};
        Vector4D(const Vector2D& v1, const Vector2D& v2) :x(v1.x), y(v1.y), z(v2.x), w(v2.y) {};
        Vector4D(const Vector3D& v, float w) :x(v.x), y(v.y), z(v.z), w(w) {};
        Vector4D(float x, const Vector3D& v) :x(x), y(v.x), z(v.y), w(v.z) {};
        ~Vector4D() {};
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
        inline Vec3 xyz() const
        {
            return Vec3(x, y, z);
        }
        inline Vec3& xyz()
        {
            return *((Vec3*)&x);
        }
        inline Vec3 rgb() const
        {
            return Vec3(r, g, b);
        }
        inline Vec3& rgb()
        {
            return *((Vec3*)&x);
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
            case 'w':
            case 'a':
                return w;
            case 1://Math::nx:
                return -x;
            case 2://Math::ny:
                return -y;
            case 3://Math::nz:
                return -z;
            case 4://Math::nw:
                return -w;
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
        inline Vec3 to() const
        {
            return Vec3(to<X>(), to<Y>(), to<Z>());
        }
        template <uchar X, uchar Y, uchar Z, uchar W>
        inline Vector4D to() const
        {
            return Vector4D(to<X>(), to<Y>(), to<Z>(), to<W>());
        }
        //-----------------------------------------------
        void normalize();
        //-----------------------------------------------
        float length() const;
        float dot(const Vector4D& vec) const;
        float distance(const Vector4D& vec) const;
        float distancePow2(const Vector4D& vec) const;
        Vector4D getNormalize() const;
        //-----------------------------------------------
        inline float squaredLength() const
        {
            return x * x + y * y + z * z + w * w;
        };
        inline void abs()
        {
            x = std::abs(x);
            y = std::abs(y);
            z = std::abs(z);
            w = std::abs(w);
        }
        inline Vector4D getAbs()const
        {
            return Vector4D(std::abs(x), std::abs(y), std::abs(z), std::abs(w));
        }
        //-----------------------------------------------
        inline float& operator [] (unsigned int i)
        {
            return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
        }
        inline bool operator==(const Vector4D& v) const
        {
            return (x == v.x && y == v.y && z == v.z && w == v.w);
        }
        inline bool operator!=(const Vector4D& v) const
        {
            return (x != v.x || y != v.y || z != v.z || w != v.w);
        }
        //-----------------------------------------------
        inline Vector4D operator+(const Vector4D& v) const
        {
            return Vector4D(x + v.x, y + v.y, z + v.z, w + v.w);
        }
        inline Vector4D operator+(float v) const
        {
            return Vector4D(x + v, y + v, z + v, w + v);
        }

        inline Vector4D operator-(const Vector4D& v) const
        {
            return Vector4D(x - v.x, y - v.y, z - v.z, w - v.w);
        }
        inline Vector4D operator-(float v) const
        {
            return Vector4D(x - v, y - v, z - v, w - v);
        }
        inline Vector4D operator-(void) const
        {
            return Vector4D(-x, -y, -z, -w);
        }
        inline Vector4D operator*(const Vector4D& v) const
        {
            return Vector4D(x * v.x, y * v.y, z * v.z, w * v.w);
        }
        inline Vector4D operator*(float v) const
        {
            return Vector4D(x * v, y * v, z * v, w * v);
        }
        inline Vector4D operator/(const Vector4D& v) const
        {
            return Vector4D(x / v.x, y / v.y, z / v.z, w / v.w);
        }
        inline Vector4D operator/(float v) const
        {
            return Vector4D(x / v, y / v, z / v, w / v);
        }
        //-----------------------------------------------
        inline const Vector4D& operator+=(const Vector4D& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
            w += v.w;
            return *this;
        }
        inline const Vector4D& operator+=(const float& v)
        {
            x += v;
            y += v;
            z += v;
            w += v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector4D& operator-=(const Vector4D& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
            w -= v.w;
            return *this;
        }
        inline const Vector4D& operator-=(const float& v)
        {
            x -= v;
            y -= v;
            z -= v;
            w -= v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector4D& operator*=(const Vector4D& v)
        {
            x *= v.x;
            y *= v.y;
            z *= v.z;
            w *= v.w;
            return *this;
        }
        inline const Vector4D& operator*=(const float& v)
        {
            x *= v;
            y *= v;
            z *= v;
            w *= v;
            return *this;
        }
        //-----------------------------------------------
        inline const Vector4D& operator/=(const Vector4D& v)
        {
            x /= v.x;
            y /= v.y;
            z /= v.z;
            w /= v.w;
            return *this;
        }
        inline const Vector4D& operator/=(const float& v)
        {
            x /= v;
            y /= v;
            z /= v;
            w /= v;
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
    inline Vector4D operator+(T v, const Vector4D& vt)
    {
        return Vector4D(v + vt.x, v + vt.y, v + vt.z, v + vt.w);
    }
    template <typename T>
    inline Vector4D operator-(T v, const Vector4D& vt)
    {
        return Vector4D(v - vt.x, v - vt.y, v - vt.z, v - vt.w);
    }
    template <typename T>
    inline Vector4D operator*(T v, const Vector4D& vt)
    {
        return Vector4D(v * vt.x, v * vt.y, v * vt.z, v * vt.w);
    }
    template <typename T>
    inline Vector4D operator/(T v, const Vector4D& vt)
    {
        return Vector4D(v / vt.x, v / vt.y, v / vt.z, v / vt.w);
    }

    //typedef
    //-----------------------------------------------
    typedef Vector4D Vec4;
}

#endif
