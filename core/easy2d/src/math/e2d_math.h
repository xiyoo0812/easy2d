#ifndef MATH_H
#define MATH_H

#include "e2d_angel.h"
#include "e2d_vector2d.h"
#include "e2d_vector3d.h"
#include "e2d_vector4d.h"
#include "e2d_matrix.h"
#include "e2d_aabb.h"
#include "e2d_rect.h"

namespace Easy2D
{
    class Math
    {
    public:
        //enum attribute
        enum VecAttribute
        {
            x = 'x', y = 'y', z = 'z', w = 'w',
            r = 'r', g = 'g', b = 'b', a = 'a',
            u = 'u', v = 'v',

            nx = 1, ny = 2, nz = 3, nw = 4,
            nr = 1, ng = 2, nb = 3, na = 4,
            nu = 1, nv = 2
        };
        //const values
        static const float PI;
        static const float PI2;
        static const float PIOVER180;
        static const float G180OVERPI;
        //radians and degrees
        static inline float torad(float deg)
        {
            return deg * PIOVER180;
        }
        static inline float todeg(float rad)
        {
            return rad * G180OVERPI;
        }
        //angles
        static inline Angle normaliseOrientation(Angle angle)
        {
            float  rotation = std::fmod(angle.valueRadians(), (float)Math::PI2);
            return Angle(Radian(rotation < 0 ? rotation += Math::PI2 : rotation));
        }

        static inline float sin(Angle angle)
        {
            return std::sin(angle.valueRadians());
        }
        static inline float cos(Angle angle)
        {
            return std::cos(angle.valueRadians());
        }

        static inline float sin(Radian angle)
        {
            return std::sin(angle.valueRadians());
        }
        static inline float cos(Radian angle)
        {
            return std::cos(angle.valueRadians());
        }

        static inline float sin(Degree angle)
        {
            return std::sin(angle.valueRadians());
        }
        static inline float cos(Degree angle)
        {
            return std::cos(angle.valueRadians());
        }

        //vector swap
        static inline void memswap(byte* a, byte* b, size_t sizeBytes)
        {
            size_t sizeTrunc = sizeBytes & ~(sizeof(size_t) - 1);
            byte* aTruncEnd = a + sizeTrunc;
            byte* aEnd = a + sizeBytes;
            size_t tmpT;
            byte   tmp1;

            while (a != aTruncEnd)
            {
                tmpT = *((size_t*)b);
                *((size_t*)b) = *((size_t*)a);
                *((size_t*)a) = tmpT;
                a += sizeof(size_t);
                b += sizeof(size_t);
            }

            while (a != aEnd)
            {
                tmp1 = *b;
                *b = *a;
                *a = tmp1;
                ++a;
                ++b;
            }
        }
        static inline void memcpy(byte* destination, const byte* source, size_t sizeBytes)
        {
            size_t sizeTrunc = sizeBytes & ~(sizeof(size_t) - 1);
            byte* destinationTruncEnd = destination + sizeTrunc;
            byte* destinationEnd = destination + sizeBytes;

            while (destination != destinationTruncEnd) {
                *((size_t*)destination) = *((size_t*)source);
                destination += sizeof(size_t);
                source += sizeof(size_t);
            }
            while (destination != destinationEnd) {
                *destination++ = *source++;
            }
        }
        //fast swap
        template<typename T>
        static inline void swap(T& x, T& y)
        {
            T temp = std::move(x);
            x = std::move(y);
            y = std::move(temp);
        }
        //infinite
        template<typename T>
        static inline bool isinf(T x)
        {
            return std::isinf(x);
        }
        //nan
        template<typename T>
        static inline bool isnan(T x)
        {
            return std::isnan(x);
        }
        //min
        template<typename T>
        static inline T min(T x, T y)
        {
            return x > y ? y : x;
        }
        static inline Vector2D min(Vector2D v1, Vector2D v2)
        {
            return Vector2D(min(v1.x, v2.x), min(v1.y, v2.y));
        }
        static inline Vector2D min(const Vector2D& v1, const Vector2D& v2)
        {
            return Vector2D(min(v1.x, v2.x), min(v1.y, v2.y));
        }
        static inline Vector3D min(Vector3D v1, Vector3D v2)
        {
            return Vector3D(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
        }
        static inline Vector3D min(const Vector3D& v1, const Vector3D& v2)
        {
            return Vector3D(min(v1.x, v2.x), min(v1.y, v2.y), min(v1.z, v2.z));
        }
        //max
        template<class T>
        static inline T max(T x, T y)
        {
            return x > y ? x : y;
        }
        static inline Vector2D max(Vector2D v1, Vector2D v2)
        {
            return Vector2D(max(v1.x, v2.x), max(v1.y, v2.y));
        }
        static inline Vector2D max(const Vector2D& v1, const Vector2D& v2)
        {
            return Vector2D(max(v1.x, v2.x), max(v1.y, v2.y));
        }
        static inline Vector3D max(Vector3D v1, Vector3D v2)
        {
            return Vector3D(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
        }
        static inline Vector3D max(const Vector3D& v1, const Vector3D& v2)
        {
            return Vector3D(max(v1.x, v2.x), max(v1.y, v2.y), max(v1.z, v2.z));
        }
        template<typename T, typename ...A>
        static inline T min(T x, A... a)
        {
            return min(x, min(a...));
        }
        template<typename T, typename ...A>
        static inline T max(T x, A... a)
        {
            return max(x, max(a...));
        }
        //lerp==linear
        template <class T, class T2>
        static inline T lerp(const T& left, const T2& right, float t)
        {
            return (T)(left + (right - left) * t);
        }
        template <class T, class T2>
        static inline T linear(const T& left, const T2& right, float t)
        {
            return (T)(left + (right - left) * t);
        }
        template <class T, class T2>
        static inline T quadratic(const T& left, const T2& right, float t)
        {
            return (T)(linear(linear(left, right, t), linear(left, right, t), t));
        }
        template <class T, class T2>
        static inline T cubic(const T& left, const T2& right, float t)
        {
            return (T)(linear(quadratic(left, right, t), quadratic(left, right, t), t));
        }
        //clamp
        template <class T, class T2, class T3>
        static inline T clamp(const T& n, const T2& max_val, const T3& min_val)
        {
            return (n > max_val ? max_val : (n < min_val ? min_val : n));
        }
        //saturate
        template <class T>
        static inline T saturate(const T& value)
        {
            return clamp(value, 1, 0);
        }
        //power of 2 test
        template <class T>
        static inline bool isPowerOfTwo(T x)
        {
            return (x != 0) && ((x & (x - 1)) == 0);
        }
        static inline uint nextPowerOfTwo(uint x)
        {
            x--;
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            x |= x >> 8;
            x |= x >> 16;
            x++;
            return x;
        }
        //prime
        static inline bool prime(unsigned int m)
        {
            unsigned int i, j;
            if (m < 2) return false;
            if (m == 2) return true;
            if (!(m & 1)) return false;
            if (m % 3 == 0) return (m == 3);
            for (i = 5; (j = i * i), j <= m && j > i; i += 6)
            {
                if (m % i == 0) return false;
                if (m % (i + 2) == 0) return false;
            }
            return true;
        }
        //sup multiple Of X
        static inline size_t multipleOfX(size_t size, size_t x) //constexpr
        {
            return ((size / x) + ((size % x) != 0)) * x;
        }
        //random values
        static void seedRandom(unsigned int seed = 0);
        static float random();
        static float randomRange(float min, float max);
        ///////////////////////////////////////////////////
        //fast factorial
        template <int n>
        struct factorial
        {
            //static
            enum { value = n * factorial<n - 1>::value };
            //dynamic
            int get()
            {
                return fac(n);
            }

        private:
            int fac(int x)
            {
                return x < 1 ? 1 : x * fac(x - 1);
            }

        };
        ///////////////////////////////////////////////////
        //fast fibonacci
        template <int n>
        struct fibonacci
        {
            //static
            enum { value = fibonacci<n - 2>::value + fibonacci<n - 1>::value };
            //dynamic
            int get()
            {
                return fib(n);
            }
        private:
            int fib(int x)
            {
                return x < 2 ? 1 : fib(x - 2) + fib(x - 1);
            }

        };
    };

    template <>
    struct Math::factorial<0>
    {
        enum { value = 1 };
    };
    template<>
    struct Math::fibonacci<0>
    {
        enum { value = 1 };
    };
    template<>
    struct Math::fibonacci<1>
    {
        enum { value = 1 };
    };
}

#endif
