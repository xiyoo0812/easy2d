#ifndef MATH_H
#define MATH_H

#include "e2d_config.h"
#include "e2d_pos.h"
#include <random>

namespace Easy2D
{
    float32 cotan(float32 x);
    float64 cotan(float64 x);
    float128 cotan(float128 x);

    template <typename T>
    T degreesToRadians(T degrees);

    template float32 degreesToRadians<float32>(float32);
    template float64 degreesToRadians<float64>(float64);
    template float128 degreesToRadians<float128>(float128);

    Vec2f degreesToRadians(const Vec2f& degrees);
    Vec3f degreesToRadians(const Vec3f& degrees);
    Vec4f degreesToRadians(const Vec4f& degrees);

    void degreesToRadians(const Vec2f& degIn, Vec2f& degOut);
    void degreesToRadians(const Vec3f& degIn, Vec3f& degOut);
    void degreesToRadians(const Vec4f& degIn, Vec4f& degOut);

    template <typename T>
    T radiansToDegrees(T radians);

    template float32 radiansToDegrees<float32>(float32);
    template float64 radiansToDegrees<float64>(float64);
    template float128 radiansToDegrees<float128>(float128);

    Vec2f radiansToDegrees(const Vec2f& radians);
    Vec3f radiansToDegrees(const Vec3f& radians);
    Vec4f radiansToDegrees(const Vec4f& radians);

    void radiansToDegrees(const Vec2f& radIn, Vec2f& radOut);
    void radiansToDegrees(const Vec3f& radIn, Vec3f& radOut);
    void radiansToDegrees(const Vec4f& radIn, Vec4f& radOut);

    template <typename T>
    T clamp(T x, T min, T max);
    template int16 clamp<int16>(int16, int16, int16);
    template uint16 clamp<uint16>(uint16, uint16, uint16);
    template uint32 clamp<uint32>(uint32, uint32, uint32);
    template int32 clamp<int32>(int32, int32, int32);
    template uint64 clamp<uint64>(uint64, uint64, uint64);
    template int64 clamp<int64>(int64, int64, int64);
    template float32 clamp<float32>(float32, float32, float32);
    template float64 clamp<float64>(float64, float64, float64);
    template float128 clamp<float128>(float128, float128, float128);

    template <typename T>
    T lerp(const T& start, const T& end, float32 percent);

    template <typename T>
    T lerp(const T& start, const T& end, float64 percent);

    Vec2f slerp(const Vec2f& start, const Vec2f& end, float32 percent);
    Vec3f slerp(const Vec3f& start, const Vec3f& end, float32 percent);
    Vec4f slerp(const Vec4f& start, const Vec4f& end, float32 percent);
    Quatf slerp(const Quatf& start, const Quatf& end, float32 percent);

    Mat2f transpose(const Mat2f& matIn);
    Mat3f transpose(const Mat3f& matIn);
    Mat4f transpose(const Mat4f& matIn);
    void transpose(const Mat2f& matIn, Mat2f& matOut);
    void transpose(const Mat3f& matIn, Mat3f& matOut);
    void transpose(const Mat4f& matIn, Mat4f& matOut);

    Mat2f inverse(const Mat2f& mat);
    Mat3f inverse(const Mat3f& mat);
    Mat4f inverse(const Mat4f& mat);
    Quatf inverse(const Quatf& quat);
    void inverse(const Mat2f& mat, Mat2f& out);
    void inverse(const Mat3f& mat, Mat3f& out);
    void inverse(const Mat4f& mat, Mat4f& out);
    void inverse(const Quatf& quat, Quatf& out);

    Mat4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up);
    void lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up, Mat4f& out);

    Vec2f log(const Vec2f& vec);
    Vec3f log(const Vec3f& vec);
    Vec4f log(const Vec4f& vec);
    Quatf log(const Quatf& quat);
    void log(const Vec2f& vecIn, Vec2f& vecOut);
    void log(const Vec3f& vecIn, Vec3f& vecOut);
    void log(const Vec4f& vecIn, Vec4f& vecOut);
    void log(const Quatf& quatIn, Quatf& quatOut);

    Vec2f log2(const Vec2f& vec);
    Vec3f log2(const Vec3f& vec);
    Vec4f log2(const Vec4f& vec);
    void log2(const Vec2f& vecIn, Vec2f& vecOut);
    void log2(const Vec3f& vecIn, Vec3f& vecOut);
    void log2(const Vec4f& vecIn, Vec4f& vecOut);

    float32 getPitch(const Quatf& quaternion);
    float32 getYaw(const Quatf& quaternion);
    float32 getRoll(const Quatf& quaternion);

    void getTranslation(const Mat4& matrix, Vec2& translation);
    void getScaling(const Mat4& matrix, Vec2& scaling);
    void getRotation(const Mat4& matrix, float32& rotation);
    void getRotationAndScaling(const Mat4& matrix, float32& rotation, Vec2& scaling);
    void decomposeMatrix(const Mat4& matrix, Vec2& position, Vec2& scaling, float32& rotation);

    int32 random(int32 min, int32 max);
    uint32 random(uint32 min, uint32 max);
    float32 random(float32 min, float32 max);
    float64 random(float64 min, float64 max);
    float128 random(float128 min, float128 max);

    float32 mag(const Vec2f& vec);
    float32 mag(const Vec3f& vec);
    float32 mag(const Vec4f& vec);

    float32 dot(const Vec2f& vecA, const Vec2f& vecB);
    float32 dot(const Vec3f& vecA, const Vec3f& vecB);
    float32 dot(const Vec4f& vecA, const Vec4f& vecB);

    float32 cross(const Vec2f& vecA, const Vec2f& vecB);
    Vec3f cross(const Vec3f& vecA, const Vec3f& vecB);
    void cross(const Vec3f& vecA, const Vec3f& vecB, Vec3f& vecOut);

    Vec2f mul(const Vec2f& vec, const Mat2f& mat);
    Vec3f mul(const Vec3f& vec, const Mat3f& mat);
    Vec4f mul(const Vec4f& vec, const Mat4f& mat);
    void mul(const Vec2f& vecIn, const Mat2f& mat, Vec2f& vecOut);
    void mul(const Vec3f& vecIn, const Mat3f& mat, Vec3f& vecOut);
    void mul(const Vec4f& vecIn, const Mat4f& mat, Vec4f& vecOut);

    Vec2f normalize(const Vec2f& vec);
    Vec3f normalize(const Vec3f& vec);
    Vec4f normalize(const Vec4f& vec);

    void normalize(const Vec2f& vecIn, Vec2f& vecOut);
    void normalize(const Vec3f& vecIn, Vec3f& vecOut);
    void normalize(const Vec4f& vecIn, Vec4f& vecOut);

    float32 distance(const Vec2f& vecA, const Vec2f& vecB);
    float32 distance(const Vec3f& vecA, const Vec3f& vecB);
    float32 distance(const Vec4f& vecA, const Vec4f& vecB);

    template <typename T>
    Vec2 distanceLine(const T& vecA, const T& vecB, const T& vecC);

    Mat3f toMat3(const Quatf& quaternion);
    void toMat3(const Quatf& quaternion, Mat3f& out);

    Mat4f toMat4(const Quatf& quaternion);
    void toMat4(const Quatf& quaternion, Mat4f& out);

    Mat4f translate(const Mat4f& mat, const Vec3f& vec);
    Mat4f translate(const Mat4f& mat, float32 x, float32 y, float32 z);
    Mat4f translate(const Vec3f& vec);
    Mat4f translate(float32 x, float32 y, float32 z);
    void translate(const Mat4f& mat, const Vec3f& vec, Mat4f& out);
    void translate(const Mat4f& mat, float32 x, float32 y, float32 z, Mat4f& out);
    void translate(const Vec3f& vec, Mat4f& out);
    void translate(float32 x, float32 y, float32 z, Mat4f& out);

    Mat4f scale(const Mat4f& mat, const Vec3f& vec);
    Mat4f scale(const Mat4f& mat, float32 x, float32 y, float32 z);
    Mat4f scale(const Vec3f& vec);
    Mat4f scale(float32 x, float32 y, float32 z);
    void scale(const Mat4f& mat, const Vec3f& vec, Mat4f& out);
    void scale(const Mat4f& mat, float32 x, float32 y, float32 z, Mat4f& out);
    void scale(const Vec3f& vec, Mat4f& out);
    void scale(float32 x, float32 y, float32 z, Mat4f& out);

    Vec2f rotate(const Vec2f& vec, float32 angle);
    Vec3f rotate(const Vec3f& vec, float32 angle, const Vec3f& normal);
    Vec4f rotate(const Vec4f& vec, float32 angle, const Vec3f& normal);
    Mat4f rotate(const Mat4f& mat, float32 angle, float32 x, float32 y, float32 z);
    Mat4f rotate(const Vec3f& vec, float32 angle);
    Mat4f rotate(float32 angle, float32 x, float32 y, float32 z);
    Vec3f rotate(const Quatf& quat, const Vec3f& vec);
    Vec4f rotate(const Quatf& quat, const Vec4f& vec);
    void rotate(const Vec2f& vec, float32 angle, Vec2f& out);
    void rotate(const Vec3f& vec, float32 angle, const Vec3f& normal, Vec3f& out);
    void rotate(const Vec4f& vec, float32 angle, const Vec3f& normal, Vec4f& out);
    void rotate(const Mat4f& mat, float32 angle, float32 x, float32 y, float32 z, Mat4f& out);
    void rotate(const Vec3f& vec, float32 angle, Mat4f& out);
    void rotate(float32 angle, float32 x, float32 y, float32 z, Mat4f& out);
    void rotate(const Quatf& quat, const Vec3f& vec, Vec3f& out);
    void rotate(const Quatf& quat, const Vec4f& vec, Vec4f& out);

    Vec2f step(const Vec2f& edge, const Vec2f& x);
    Vec3f step(const Vec3f& edge, const Vec3f& x);
    Vec4f step(const Vec4f& edge, const Vec4f& x);

    Vec2f step(const Vec2f& edge, float32 x);
    Vec3f step(const Vec3f& edge, float32 x);
    Vec4f step(const Vec4f& edge, float32 x);

    void step(const Vec2f& edge, const Vec2f& x, Vec2f& out);
    void step(const Vec3f& edge, const Vec3f& x, Vec3f& out);
    void step(const Vec4f& edge, const Vec4f& x, Vec4f& out);

    void step(const Vec2f& edge, float32 x, Vec2f& out);
    void step(const Vec3f& edge, float32 x, Vec3f& out);
    void step(const Vec4f& edge, float32 x, Vec4f& out);

    template <typename T>
    T saturate(T x);

    Vec2f saturate(const Vec2f& vec);
    Vec3f saturate(const Vec3f& vec);
    Vec4f saturate(const Vec4f& vec);

    void saturate(const Vec2f& vecIn, Vec2f& vecOut);
    void saturate(const Vec3f& vecIn, Vec3f& vecOut);
    void saturate(const Vec4f& vecIn, Vec4f& vecOut);

    Vec2f refract(const Vec2f& I, const Vec2f& N, float32 eta);
    Vec3f refract(const Vec3f& I, const Vec3f& N, float32 eta);
    Vec4f refract(const Vec4f& I, const Vec4f& N, float32 eta);

    void refract(const Vec2f& I, const Vec2f& N, float32 eta, Vec2f& out);
    void refract(const Vec3f& I, const Vec3f& N, float32 eta, Vec3f& out);
    void refract(const Vec4f& I, const Vec4f& N, float32 eta, Vec4f& out);

    uint32 mod(uint32 x, uint32 y);
    int32 mod(int32 x, int32 y);
    float32 mod(float32 x, float32 y);
    float64 mod(float64 x, float64 y);

    Vec2f mod(const Vec2f& x, const Vec2f& y);
    Vec3f mod(const Vec3f& x, const Vec3f& y);
    Vec4f mod(const Vec4f& x, const Vec4f& y);

    void mod(const Vec2f& x, const Vec2f& y, Vec2f& out);
    void mod(const Vec3f& x, const Vec3f& y, Vec3f& out);
    void mod(const Vec4f& x, const Vec4f& y, Vec4f& out);

    Vec2f mod(const Vec2f& x, float32 y);
    Vec3f mod(const Vec3f& x, float32 y);
    Vec4f mod(const Vec4f& x, float32 y);

    void mod(const Vec2f& x, float32 y, Vec2f& out);
    void mod(const Vec3f& x, float32 y, Vec3f& out);
    void mod(const Vec4f& x, float32 y, Vec4f& out);

    Mat3f reflect(const Mat3f& mat, const Vec3f& normal);
    void reflect(const Mat3f& matIn, const Vec3f& normal, Mat3f& matOut);

    Mat3f project(const Mat3f& mat, const Vec3f& normal);
    void project(const Mat3f& matIn, const Vec3f& normal, Mat3f& matOut);

    Vec3 project(const Vec3& pos, const Mat4& model, const Mat4& proj, const Vec4& viewport);
    Vec3 unProject(const Vec3& pos, const Mat4& model, const Mat4& proj, const Vec4& viewport);

    const float32* toPointer(const Mat2f& mat);
    const float32* toPointer(const Mat3f& mat);
    const float32* toPointer(const Mat4f& mat);
    const float32* toPointer(const Vec2f& vec);
    const float32* toPointer(const Vec3f& vec);
    const float32* toPointer(const Vec4f& vec);
    const float32* toPointer(const Quatf& quat);

    Pos lerp(const Pos& start, const Pos& end, float32 percent);
    Pos slerp(const Pos& start, const Pos& end, float32 percent);
    Pos nlerp(const Pos& start, const Pos& end, float32 percent);
    float32 mag(const Pos& pos);
    float32 dot(const Pos& posA, const Pos& posB);
    Pos mul(const Pos& position, const Mat2f& mat);
    void mul(const Pos& posIn, const Mat2f& mat, Pos& posOut);
    Pos normalize(const Pos& position);
    void normalize(const Pos& posIn, Pos& posOut);
    float32 distance(const Pos& posA, const Pos& posB);
    Mat4f translate(const Pos& pos);
    Mat4f translate(const Mat4f& mat, const Pos& pos);
    void translate(const Pos& pos, Mat4f& out);
    void translate(const Mat4f& mat, const Pos& pos, Mat4f& out);
    Mat4f scale(const Pos& pos);
    Mat4f scale(const Mat4f& mat, const Pos& pos);
    void scale(const Pos& pos, Mat4f& out);
    void scale(const Mat4f& mat, const Pos& pos, Mat4f& out);
    Mat4f lookAt(const Pos& eye, const Pos& center);
    void lookAt(const Pos& eye, const Pos& center, Mat4f& out);
    Pos log(const Pos& pos);
    void log(const Pos& posIn, Pos& posOut);
    Pos log2(const Pos& pos);
    void log2(const Pos& posIn, Pos& posOut);
    Pos step(const Pos& pos, const Vec2f& x);
    Pos step(const Pos& pos, float32 x);
    void step(const Pos& posIn, const Vec2f& x, Pos& posOut);
    void step(const Pos& posIn, float32 x, Pos& posOut);
    Pos mod(const Pos& pos, const Vec2f& mod);
    Pos mod(const Pos& pos, float32 mod);
    void mod(const Pos& posIn, const Vec2f& mod, Pos& posOut);
    void mod(const Pos& posIn, float32 mod, Pos& posOut);

    bool posInRect(const Vec2& leftTop, const Vec2& size, const Vec2& pos);

    inline static std::mt19937 mMt19937 = std::mt19937(std::random_device()());
}

#include "e2d_math.hpp"

#endif
