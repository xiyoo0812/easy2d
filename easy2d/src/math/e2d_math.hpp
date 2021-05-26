#include "e2d_math.h"

namespace Easy2D
{
    template <typename T>
    T degreesToRadians(T degrees)
    {
        return T(float64(degrees) * PI / 180);
    }

    template <typename T>
    T radiansToDegrees(T radians)
    {
        return T(float64(radians) * 180 / PI);
    }

    template <typename T>
    T clamp(T x, T min, T max)
    {
        return x < min ? min : (x > max ? max : x);
    }

    template <typename T>
    T lerp(const T & start, const T & end, float32 percent)
    {
        return start + percent * (end - start);
    }

    template <typename T>
    T lerp(const T & start, const T & end, float64 percent)
    {
        return start + percent * (end - start);
    }

    template <typename T>
    T saturate(T x)
    {
        return glm::saturate<T>(x);
    }

}