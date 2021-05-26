#ifndef POS_H
#define POS_H

#include "base\e2d_types.h"

namespace Easy2D
{
    class Pos
    {
    public:
        float32 x = 0, y = 0;
        lay l = 0;

        Pos();
        explicit Pos(const Vec2& vec, lay layer = 0);
        Pos(float64 X, float64 Y, lay layer = 0);
        Pos(float32 X, float32 Y, lay layer = 0);
        Pos(int32 X, int32 Y, lay layer = 0);
        Pos(int64 X, int64 Y, lay layer = 0);
        Pos(const Pos& yRef);
        Pos(Pos && yRef);

        bool operator==(const Pos& yRef) const;
        bool operator==(const Vec2& yRef) const;
        bool operator!=(const Pos& yRef) const;
        bool operator!=(const Vec2& yRef) const;

        Pos& operator=(const Pos& yRef);
        Pos& operator=(Pos && yRef);
        Pos& operator=(const Vec2& yRef);
        Pos& operator+=(const Pos& yRef);
        Pos& operator+=(const Vec2& yRef);
        Pos& operator-=(const Pos& yRef);
        Pos& operator-=(const Vec2& yRef);
        Pos& operator*=(uint32 n);
        Pos& operator*=(uint64 n);
        Pos& operator*=(int32 n);
        Pos& operator*=(int64 n);
        Pos& operator*=(float32 n);
        Pos& operator*=(float64 n);
        Pos& operator/=(uint32 n);
        Pos& operator/=(uint64 n);
        Pos& operator/=(int32 n);
        Pos& operator/=(int64 n);
        Pos& operator/=(float32 n);
        Pos& operator/=(float64 n);


        Pos operator+(const Pos& yRef) const;
        Pos operator+(const Vec2& yRef) const;
        Pos operator-(const Pos& yRef) const;
        Pos operator-(const Vec2& yRef) const;
        Pos operator*(uint32 n);
        Pos operator*(uint64 n);
        Pos operator*(int32 n);
        Pos operator*(int64 n);
        Pos operator*(float32 n);
        Pos operator*(float64 n);
        Pos operator/(uint32 n);
        Pos operator/(uint64 n);
        Pos operator/(int32 n);
        Pos operator/(int64 n);
        Pos operator/(float32 n);
        Pos operator/(float64 n);

        Vec2 pos2D() const;
        Vec3 pos3D() const;

        float32 length() const;
    };
}

#endif
