#include "e2d_math.h"

namespace Easy2D
{
    float32 cotan(float32 x)
    {
        return 1.0f / tan(x);
    }

    float64 cotan(float64 x)
    {
        return 1.0 / tan(x);
    }

    float128 cotan(float128 x)
    {
        return 1.0 / tan(x);
    }

    Vec2f degreesToRadians(const Vec2f& degrees)
    {
        Vec2f vec;
        vec.x = degreesToRadians(degrees.x);
        vec.y = degreesToRadians(degrees.y);
        return vec;
    }

    Vec3f degreesToRadians(const Vec3f& degrees)
    {
        Vec3f vec;
        vec.x = degreesToRadians(degrees.x);
        vec.y = degreesToRadians(degrees.y);
        vec.z = degreesToRadians(degrees.z);
        return vec;
    }

    Vec4f degreesToRadians(const Vec4f& degrees)
    {
        Vec4f vec;
        vec.x = degreesToRadians(degrees.x);
        vec.y = degreesToRadians(degrees.y);
        vec.z = degreesToRadians(degrees.z);
        vec.w = degreesToRadians(degrees.w);
        return vec;
    }

    void degreesToRadians(const Vec2f& degIn, Vec2f& degOut)
    {
        degOut.x = degreesToRadians(degIn.x);
        degOut.y = degreesToRadians(degIn.y);
    }

    void degreesToRadians(const Vec3f& degIn, Vec3f& degOut)
    {
        degOut.x = degreesToRadians(degIn.x);
        degOut.y = degreesToRadians(degIn.y);
        degOut.z = degreesToRadians(degIn.z);
    }

    void degreesToRadians(const Vec4f& degIn, Vec4f& degOut)
    {
        degOut.x = degreesToRadians(degIn.x);
        degOut.y = degreesToRadians(degIn.y);
        degOut.z = degreesToRadians(degIn.z);
        degOut.w = degreesToRadians(degIn.w);
    }

    Vec2f radiansToDegrees(const Vec2f& radians)
    {
        Vec2f vec;
        vec.x = radiansToDegrees(radians.x);
        vec.y = radiansToDegrees(radians.y);
        return vec;
    }

    Vec3f radiansToDegrees(const Vec3f& radians)
    {
        Vec3f vec;
        vec.x = radiansToDegrees(radians.x);
        vec.y = radiansToDegrees(radians.y);
        vec.z = radiansToDegrees(radians.z);
        return vec;
    }

    Vec4f radiansToDegrees(const Vec4f& radians)
    {
        Vec4f vec;
        vec.x = radiansToDegrees(radians.x);
        vec.y = radiansToDegrees(radians.y);
        vec.z = radiansToDegrees(radians.z);
        vec.w = radiansToDegrees(radians.w);
        return vec;
    }

    void radiansToDegrees(const Vec2f& radIn, Vec2f& radOut)
    {
        radOut.x = radiansToDegrees(radIn.x);
        radOut.y = radiansToDegrees(radIn.y);
    }

    void radiansToDegrees(const Vec3f& radIn, Vec3f& radOut)
    {
        radOut.x = radiansToDegrees(radIn.x);
        radOut.y = radiansToDegrees(radIn.y);
        radOut.z = radiansToDegrees(radIn.z);
    }

    void radiansToDegrees(const Vec4f& radIn, Vec4f& radOut)
    {
        radOut.x = radiansToDegrees(radIn.x);
        radOut.y = radiansToDegrees(radIn.y);
        radOut.z = radiansToDegrees(radIn.z);
        radOut.w = radiansToDegrees(radIn.w);
    }

    Vec2f slerp(const Vec2f& start, const Vec2f& end, float32 percent)
    {
        float32 dot = Easy2D::dot(start, end);
        dot = clamp(dot, -1.0f, 1.0f);
        float32 theta = acos(dot) * percent;
        Vec2f relativeVec = end - start * dot;
        relativeVec = Easy2D::normalize(relativeVec);
        return (start * float32(cos(theta))) + (relativeVec * float32(sin(theta)));
    }

    Vec3f slerp(const Vec3f& start, const Vec3f& end, float32 percent)
    {
        float32 dot = Easy2D::dot(start, end);
        dot = clamp(dot, -1.0f, 1.0f);
        float32 theta = acos(dot) * percent;
        Vec3f relativeVec = end - start * dot;
        relativeVec = Easy2D::normalize(relativeVec);
        return (start * float32(cos(theta))) + (relativeVec * float32(sin(theta)));
    }

    Vec4f slerp(const Vec4f& start, const Vec4f& end, float32 percent)
    {
        float32 dot = Easy2D::dot(start, end);
        dot = clamp(dot, -1.0f, 1.0f);
        float32 theta = acos(dot) * percent;
        Vec4f relativeVec = end - start * dot;
        relativeVec = Easy2D::normalize(relativeVec);
        return (start * float32(cos(theta))) + (relativeVec * float32(sin(theta)));
    }

    Quatf slerp(const Quatf& start, const Quatf& end, float32 percent)
    {
        Vec4f vec = Easy2D::slerp(
            Vec4f(start.x, start.y, start.z, start.w),
            Vec4f(end.x, end.y, end.z, end.w),
            percent);
        return Quatf(vec.x, vec.y, vec.z, vec.w);
    }

    Vec2f nlerp(const Vec2f& start, const Vec2f& end, float32 percent)
    {
        Vec2f result = lerp(start, end, percent);
        Easy2D::normalize(result, result);
        return result;
    }

    Vec3f nlerp(const Vec3f& start, const Vec3f& end, float32 percent)
    {
        Vec3f result = lerp(start, end, percent);
        Easy2D::normalize(result, result);
        return result;
    }

    Vec4f nlerp(const Vec4f& start, const Vec4f& end, float32 percent)
    {
        Vec4f result = lerp(start, end, percent);
        normalize(result, result);
        return result;
    }

    Quatf nlerp(const Quatf& start, const Quatf& end, float32 percent)
    {
        Vec4f vec = lerp(
            Vec4f(start.x, start.y, start.z, start.w),
            Vec4f(end.x, end.y, end.z, end.w),
            percent);
        normalize(vec, vec);
        return Quatf(vec.x, vec.y, vec.z, vec.w);
    }

    Mat2f transpose(const Mat2f& matrix)
    {
        return glm::transpose(matrix);
    }

    Mat3f transpose(const Mat3f& matrix)
    {
        return glm::transpose(matrix);
    }

    Mat4f transpose(const Mat4f& matrix)
    {
        return glm::transpose(matrix);
    }

    void transpose(const Mat2f& matIn, Mat2f& matOut)
    {
        matOut = glm::transpose(matIn);
    }

    void transpose(const Mat3f& matIn, Mat3f& matOut)
    {
        matOut = glm::transpose(matIn);
    }

    void transpose(const Mat4f& matIn, Mat4f& matOut)
    {
        matOut = glm::transpose(matIn);
    }

    Mat2f inverse(const Mat2f& mat)
    {
        return glm::inverse<float32>(mat);
    }

    Mat3f inverse(const Mat3f& mat)
    {
        return glm::inverse<float32>(mat);
    }

    Mat4f inverse(const Mat4f& mat)
    {
        return glm::inverse<float32>(mat);
    }

    Quatf inverse(const Quatf& quat)
    {
        return glm::inverse<float32>(quat);
    }

    void inverse(const Mat2f& mat, Mat2f& out)
    {
        out = glm::inverse<float32>(mat);
    }

    void inverse(const Mat3f& mat, Mat3f& out)
    {
        out = glm::inverse<float32>(mat);
    }

    void inverse(const Mat4f& mat, Mat4f& out)
    {
        out = glm::inverse<float32>(mat);
    }

    void inverse(const Quatf& quat, Quatf& out)
    {
        out = glm::inverse<float32>(quat);
    }

    Mat4f lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up)
    {
        return glm::lookAt<float32>(eye, center, up);
    }

    void lookAt(const Vec3f& eye, const Vec3f& center, const Vec3f& up, Mat4f& out)
    {
        out = glm::lookAt<float32>(eye, center, up);
    }

    Vec2f log(const Vec2f& vec)
    {
        return glm::log<float32>(vec);
    }

    Vec3f log(const Vec3f& vec)
    {
        return glm::log<float32>(vec);
    }

    Vec4f log(const Vec4f& vec)
    {
        return glm::log<float32>(vec);
    }

    Quatf log(const Quatf& quat)
    {
        return glm::log<float32>(quat);
    }

    void log(const Vec2f& vecIn, Vec2f& vecOut)
    {
        vecOut = glm::log<float32>(vecIn);
    }

    void log(const Vec3f& vecIn, Vec3f& vecOut)
    {
        vecOut = glm::log<float32>(vecIn);
    }

    void log(const Vec4f& vecIn, Vec4f& vecOut)
    {
        vecOut = glm::log<float32>(vecIn);
    }

    void log(const Quatf& quatIn, Quatf& quatOut)
    {
        quatOut = glm::log<float32>(quatIn);
    }

    Vec2f log2(const Vec2f& vec)
    {
        return glm::log2<float32>(vec);
    }

    Vec3f log2(const Vec3f& vec)
    {
        return glm::log2<float32>(vec);
    }

    Vec4f log2(const Vec4f& vec)
    {
        return glm::log2<float32>(vec);
    }

    void log2(const Vec2f& vecIn, Vec2f& vecOut)
    {
        vecOut = glm::log2<float32>(vecIn);
    }

    void log2(const Vec3f& vecIn, Vec3f& vecOut)
    {
        vecOut = glm::log2<float32>(vecIn);
    }

    void log2(const Vec4f& vecIn, Vec4f& vecOut)
    {
        vecOut = glm::log2<float32>(vecIn);
    }

    float32 getPitch(const Quatf& quaternion)
    {
        return float32(atan2f(2 * (
            quaternion.y * quaternion.z +
            quaternion.w * quaternion.x),
            quaternion.w * quaternion.w -
            quaternion.x * quaternion.x -
            quaternion.y * quaternion.y +
            quaternion.z * quaternion.z
        ));
    }

    float32 getYaw(const Quatf& quaternion)
    {
        return float32(asinf(-2 * (
            quaternion.x * quaternion.z -
            quaternion.w * quaternion.y
            )));
    }

    float32 getRoll(const Quatf& quaternion)
    {
        return float32(atan2f(2 * (
            quaternion.x * quaternion.y +
            quaternion.w * quaternion.z),
            quaternion.w * quaternion.w +
            quaternion.x * quaternion.x -
            quaternion.y * quaternion.y -
            quaternion.z * quaternion.z
        ));
    }

    void getTranslation(const Mat4& matrix, Vec2& translation)
    {
        translation.x = matrix[3][0];
        translation.y = matrix[3][1];
    }

    void getScaling(const Mat4& matrix, Vec2& scaling)
    {
        scaling.x = sqrt(
            pow(matrix[0][0], 2) +
            pow(matrix[1][0], 2) +
            pow(matrix[2][0], 2)
        );
        scaling.y = sqrt(
            pow(matrix[0][1], 2) +
            pow(matrix[1][1], 2) +
            pow(matrix[2][1], 2)
        );
    }

    void getRotation(const Mat4& matrix, float32& rotation)
    {
        Vec2 scaling;
        Easy2D::getRotationAndScaling(matrix, rotation, scaling);
    }

    void getRotationAndScaling(const Mat4& matrix, float32& rotation, Vec2& scaling)
    {
        Easy2D::getScaling(matrix, scaling);

        Mat4 rot;
        if (scaling.x != 0)
        {
            rot[0][0] = matrix[0][0] / scaling.x;
            rot[0][1] = matrix[0][1] / scaling.x;
            rot[0][2] = matrix[0][2] / scaling.x;
            rot[0][3] = 0;
        }

        if (scaling.y != 0)
        {
            rot[1][0] = matrix[1][0] / scaling.y;
            rot[1][1] = matrix[1][1] / scaling.y;
            rot[1][2] = matrix[1][2] / scaling.y;
            rot[1][3] = 0;
        }

        rot[2][0] = matrix[2][0];
        rot[2][1] = matrix[2][1];
        rot[2][2] = matrix[2][2];
        rot[2][3] = 0;

        rot[3][0] = 0;
        rot[3][1] = 0;
        rot[3][2] = 0;
        rot[3][3] = 1;
        Quat rotQuat(rot);
        rotation = Easy2D::getRoll(rotQuat);
    }

    void decomposeMatrix(const Mat4& matrix, Vec2& position, Vec2& scaling, float32& rotation)
    {
        Easy2D::getTranslation(matrix, position);
        Easy2D::getRotationAndScaling(matrix, rotation, scaling);
    }

    Vec3 project(const Vec3& pos, const Mat4& model, const Mat4& proj, const Vec4& viewport)
    {
        return glm::project<float32, float32>(pos, model, proj, viewport);
    }

    Vec3 unProject(const Vec3& pos, const Mat4& model, const Mat4& proj, const Vec4& viewport)
    {
        return glm::unProject<float32, float32>(pos, model, proj, viewport);
    }

    int32 random(int32 min, int32 max)
    {
        std::uniform_int_distribution<int32> dist(min, max);
        return dist(mMt19937);
    }

    uint32 random(uint32 min, uint32 max)
    {
        std::uniform_int_distribution<uint32> dist(min, max);
        return dist(mMt19937);
    }

    float32 random(float32 min, float32 max)
    {
        std::uniform_real_distribution<float32> dist(min, max);
        return dist(mMt19937);
    }

    float64 random(float64 min, float64 max)
    {
        std::uniform_real_distribution<float64> dist(min, max);
        return dist(mMt19937);
    }

    float128 random(float128 min, float128 max)
    {
        std::uniform_real_distribution<float128> dist(min, max);
        return dist(mMt19937);
    }

    float32 mag(const Vec2f& vec)
    {
        return glm::length<float32>(vec);
    }

    float32 mag(const Vec3f& vec)
    {
        return glm::length<float32>(vec);
    }

    float32 mag(const Vec4f& vec)
    {
        return glm::length<float32>(vec);
    }

    float32 dot(const Vec2f& vecA, const Vec2f& vecB)
    {
        return glm::dot<float32>(vecA, vecB);
    }

    float32 dot(const Vec3f& vecA, const Vec3f& vecB)
    {
        return glm::dot<float32>(vecA, vecB);
    }

    float32 dot(const Vec4f& vecA, const Vec4f& vecB)
    {
        return glm::dot<float32>(vecA, vecB);
    }

    float32 cross(const Vec2f& vecA, const Vec2f& vecB)
    {
        return vecA.x * vecB.y - vecA.y * vecB.x;
    }

    Vec3f cross(const Vec3f& vecA, const Vec3f& vecB)
    {
        return glm::cross<float32>(vecA, vecB);
    }

    void cross(const Vec3f& vecA, const Vec3f& vecB, Vec3f& vecOut)
    {
        vecOut = glm::cross<float32>(vecA, vecB);
    }

    Vec2f mul(const Vec2f& vec, const Mat2f& mat)
    {
        return glm::mul<float32>(vec, mat);
    }

    Vec3f mul(const Vec3f& vec, const Mat3f& mat)
    {
        return glm::mul<float32>(vec, mat);
    }

    Vec4f mul(const Vec4f& vec, const Mat4f& mat)
    {
        return glm::mul<float32>(vec, mat);
    }

    void mul(const Vec2f& vecIn, const Mat2f& mat, Vec2f& vecOut)
    {
        vecOut = glm::mul<float32>(vecIn, mat);
    }

    void mul(const Vec3f& vecIn, const Mat3f& mat, Vec3f& vecOut)
    {
        vecOut = glm::mul<float32>(vecIn, mat);
    }

    void mul(const Vec4f& vecIn, const Mat4f& mat, Vec4f& vecOut)
    {
        vecOut = glm::mul<float32>(vecIn, mat);
    }

    Vec2f normalize(const Vec2f& vec)
    {
        return glm::normalize<float32>(vec);
    }

    Vec3f normalize(const Vec3f& vec)
    {
        return glm::normalize<float32>(vec);
    }

    Vec4f normalize(const Vec4f& vec)
    {
        return glm::normalize<float32>(vec);
    }

    void normalize(const Vec2f& vecIn, Vec2f& vecOut)
    {
        vecOut = glm::normalize<float32>(vecIn);
    }

    void normalize(const Vec4f& vecIn, Vec4f& vecOut)
    {
        vecOut = glm::normalize<float32>(vecIn);
    }

    void normalize(const Vec3f& vecIn, Vec3f& vecOut)
    {
        vecOut = glm::normalize<float32>(vecIn);
    }

    float32 distance(const Vec2f& vecA, const Vec2f& vecB)
    {
        return glm::distance<float32>(vecA, vecB);
    }

    float32 distance(const Vec3f& vecA, const Vec3f& vecB)
    {
        return glm::distance<float32>(vecA, vecB);
    }

    float32 distance(const Vec4f& vecA, const Vec4f& vecB)
    {
        return glm::distance<float32>(vecA, vecB);
    }

    Mat3f toMat3(const Quatf& quaternion)
    {
        return glm::toMat3<float32>(quaternion);
    }

    void toMat3(const Quatf& quaternion, Mat3f& out)
    {
        out = glm::toMat3<float32>(quaternion);
    }

    Mat4f toMat4(const Quatf& quaternion)
    {
        return glm::toMat4<float32>(quaternion);
    }

    void toMat4(const Quatf& quaternion, Mat4f& out)
    {
        out = glm::toMat4<float32>(quaternion);
    }

    Mat4f translate(const Mat4f& mat, const Vec3f& vec)
    {
        return glm::translate<float32>(mat, vec);
    }

    Mat4f translate(const Mat4f& mat, float32 x, float32 y, float32 z)
    {
        return glm::translate<float32>(mat, x, y, z);
    }

    Mat4f translate(const Vec3f& vec)
    {
        return glm::translate<float32>(vec);
    }

    Mat4f translate(float32 x, float32 y, float32 z)
    {
        return glm::translate<float32>(x, y, z);
    }

    void translate(const Mat4f& mat, const Vec3f& vec, Mat4f& out)
    {
        out = glm::translate<float32>(mat, vec);
    }

    void translate(const Mat4f& mat, float32 x, float32 y, float32 z, Mat4f& out)
    {
        out = glm::translate<float32>(mat, x, y, z);
    }

    void translate(const Vec3f& vec, Mat4f& out)
    {
        out = glm::translate<float32>(vec);
    }

    void translate(float32 x, float32 y, float32 z, Mat4f& out)
    {
        out = glm::translate<float32>(x, y, z);
    }

    Mat4f scale(const Mat4f& mat, const Vec3f& vec)
    {
        return glm::scale<float32>(mat, vec);
    }

    Mat4f scale(const Mat4f& mat, float32 x, float32 y, float32 z)
    {
        return glm::scale<float32>(mat, x, y, z);
    }

    Mat4f scale(const Vec3f& vec)
    {
        return glm::scale<float32>(vec);
    }

    Mat4f scale(float32 x, float32 y, float32 z)
    {
        return glm::scale<float32>(x, y, z);
    }

    void scale(const Mat4f& mat, const Vec3f& vec, Mat4f& out)
    {
        out = glm::scale<float32>(mat, vec);
    }

    void scale(const Mat4f& mat, float32 x, float32 y, float32 z, Mat4f& out)
    {
        out = glm::scale<float32>(mat, x, y, z);
    }

    void scale(const Vec3f& vec, Mat4f& out)
    {
        out = glm::scale<float32>(vec);
    }

    void scale(float32 x, float32 y, float32 z, Mat4f& out)
    {
        out = glm::scale<float32>(x, y, z);
    }

    Vec2f rotate(const Vec2f& vec, float32 angle)
    {
        return glm::rotate(vec, angle);
    }

    Vec3f rotate(const Vec3f& vec, float32 angle, const Vec3f& normal)
    {
        return glm::rotate(vec, angle, normal);
    }

    Vec4f rotate(const Vec4f& vec, float32 angle, const Vec3f& normal)
    {
        return glm::rotate(vec, angle, normal);
    }

    Mat4f rotate(const Mat4f& mat, float32 angle, float32 x, float32 y, float32 z)
    {
        return glm::rotate(mat, angle, x, y, z);
    }

    Mat4f rotate(const Vec3f& vec, float32 angle)
    {
        return glm::rotate(angle, vec);
    }

    Mat4f rotate(float32 angle, float32 x, float32 y, float32 z)
    {
        return glm::rotate(angle, x, y, z);
    }

    Vec3f rotate(const Quatf& quat, const Vec3f& vec)
    {
        return glm::rotate(quat, vec);
    }

    Vec4f rotate(const Quatf& quat, const Vec4f& vec)
    {
        return glm::rotate(quat, vec);
    }

    void rotate(const Vec2f& vec, float32 angle, Vec2f& out)
    {
        out = glm::rotate(vec, angle);
    }

    void rotate(const Vec3f& vec, float32 angle, const Vec3f& normal, Vec3f& out)
    {
        out = glm::rotate(vec, angle, normal);
    }

    void rotate(const Vec4f& vec, float32 angle, const Vec3f& normal, Vec4f& out)
    {
        out = glm::rotate(vec, angle, normal);
    }

    void rotate(const Mat4f& mat, float32 angle, float32 x, float32 y, float32 z, Mat4f& out)
    {
        out = glm::rotate(mat, angle, x, y, z);
    }

    void rotate(const Vec3f& vec, float32 angle, Mat4f& out)
    {
        out = glm::rotate(angle, vec);
    }

    void rotate(float32 angle, float32 x, float32 y, float32 z, Mat4f& out)
    {
        out = glm::rotate(angle, x, y, z);
    }

    void rotate(const Quatf& quat, const Vec3f& vec, Vec3f& out)
    {
        out = glm::rotate(quat, vec);
    }

    void rotate(const Quatf& quat, const Vec4f& vec, Vec4f& out)
    {
        out = glm::rotate(quat, vec);
    }

    Vec2f step(const Vec2f& edge, const Vec2f& x)
    {
        return glm::step<float32>(edge, x);
    }

    Vec3f step(const Vec3f& edge, const Vec3f& x)
    {
        return glm::step<float32>(edge, x);
    }

    Vec4f step(const Vec4f& edge, const Vec4f& x)
    {
        return glm::step<float32>(edge, x);
    }

    Vec2f step(const Vec2f& edge, float32 x)
    {
        Vec2f vec(x, x);
        return glm::step<float32>(edge, vec);
    }

    Vec3f step(const Vec3f& edge, float32 x)
    {
        Vec3f vec(x, x, x);
        return glm::step<float32>(edge, vec);
    }

    Vec4f step(const Vec4f& edge, float32 x)
    {
        Vec4f vec(x, x, x, x);
        return glm::step<float32>(edge, vec);
    }

    void step(const Vec2f& edge, const Vec2f& x, Vec2f& out)
    {
        out = glm::step<float32>(edge, x);
    }

    void step(const Vec3f& edge, const Vec3f& x, Vec3f& out)
    {
        out = glm::step<float32>(edge, x);
    }

    void step(const Vec4f& edge, const Vec4f& x, Vec4f& out)
    {
        out = glm::step<float32>(edge, x);
    }

    void step(const Vec2f& edge, float32 x, Vec2f& out)
    {
        Vec2f vec(x, x);
        out = glm::step<float32>(edge, vec);
    }

    void step(const Vec3f& edge, float32 x, Vec3f& out)
    {
        Vec3f vec(x, x, x);
        out = glm::step<float32>(edge, vec);
    }

    void step(const Vec4f& edge, float32 x, Vec4f& out)
    {
        Vec4f vec(x, x, x, x);
        out = glm::step<float32>(edge, vec);
    }

    Vec2f saturate(const Vec2f& vec)
    {
        return glm::saturate<float32>(vec);
    }

    Vec3f saturate(const Vec3f& vec)
    {
        return glm::saturate<float32>(vec);
    }

    Vec4f saturate(const Vec4f& vec)
    {
        return glm::saturate<float32>(vec);
    }

    void saturate(const Vec2f& vecIn, Vec2f& vecOut)
    {
        vecOut = glm::saturate<float32>(vecIn);
    }

    void saturate(const Vec3f& vecIn, Vec3f& vecOut)
    {
        vecOut = glm::saturate<float32>(vecIn);
    }

    void saturate(const Vec4f& vecIn, Vec4f& vecOut)
    {
        vecOut = glm::saturate<float32>(vecIn);
    }

    Vec2f refract(const Vec2f& I, const Vec2f& N, float32 eta)
    {
        return glm::refract(I, N, eta);
    }

    Vec3f refract(const Vec3f& I, const Vec3f& N, float32 eta)
    {
        return glm::refract(I, N, eta);
    }

    Vec4f refract(const Vec4f& I, const Vec4f& N, float32 eta)
    {
        return glm::refract(I, N, eta);
    }

    void refract(const Vec2f& I, const Vec2f& N, float32 eta, Vec2f& out)
    {
        out = glm::refract(I, N, eta);
    }

    void refract(const Vec3f& I, const Vec3f& N, float32 eta, Vec3f& out)
    {
        out = glm::refract(I, N, eta);
    }

    void refract(const Vec4f& I, const Vec4f& N, float32 eta, Vec4f& out)
    {
        out = glm::refract(I, N, eta);
    }

    uint32 mod(uint32 x, uint32 y)
    {
        return x % y;
    }

    int32 mod(int32 x, int32 y)
    {
        return x % y;
    }

    float32 mod(float32 x, float32 y)
    {
        return glm::modf<float32>(x, y);
    }

    float64 mod(float64 x, float64 y)
    {
        return glm::modf<float64>(x, y);
    }

    Vec2f mod(const Vec2f& x, const Vec2f& y)
    {
        return glm::mod<float32>(x, y);
    }

    Vec3f mod(const Vec3f& x, const Vec3f& y)
    {
        return glm::mod<float32>(x, y);
    }

    Vec4f mod(const Vec4f& x, const Vec4f& y)
    {
        return glm::mod<float32>(x, y);
    }

    void mod(const Vec2f& x, const Vec2f& y, Vec2f& out)
    {
        out = glm::mod<float32>(x, y);
    }

    void mod(const Vec3f & x, const Vec3f & y, Vec3f& out)
    {
        out = glm::mod<float32>(x, y);
    }

    void mod(const Vec4f& x, const Vec4f& y, Vec4f& out)
    {
        out = glm::mod<float32>(x, y);
    }

    Vec2f mod(const Vec2f& x, float32 y)
    {
        return glm::mod<float32>(x, Vec2f(y, y));
    }

    Vec3f mod(const Vec3f& x, float32 y)
    {
        return glm::mod<float32>(x, Vec3f(y, y, y));
    }

    Vec4f mod(const Vec4f& x, float32 y)
    {
        return glm::mod<float32>(x, Vec4f(y, y, y, y));
    }

    void mod(const Vec2f& x, float32 y, Vec2f& out)
    {
        out = glm::mod<float32>(x, Vec2f(y, y));
    }

    void mod(const Vec3f& x, float32 y, Vec3f& out)
    {
        out = glm::mod<float32>(x, Vec3f(y, y, y));
    }

    void mod(const Vec4f& x, float32 y, Vec4f& out)
    {
        out = glm::mod<float32>(x, Vec4f(y, y, y, y));
    }

    Mat3f reflect(const Mat3f& mat, const Vec3f& normal)
    {
        return glm::reflect2D<float32>(mat, normal);
    }

    void reflect(const Mat3f& matIn, const Vec3f& normal, Mat3f& matOut)
    {
        matOut = glm::reflect2D<float32>(matIn, normal);
    }

    Mat3f project(const Mat3f& mat, const Vec3f& normal)
    {
        return glm::proj2D<float32>(mat, normal);
    }

    void project(const Mat3f& matIn, const Vec3f& normal, Mat3f& matOut)
    {
        matOut = glm::proj2D<float32>(matIn, normal);
    }

    const float32* toPointer(const Mat2f& mat)
    {
        return glm::value_ptr<float32>(mat);
    }

    const float32* toPointer(const Mat3f& mat)
    {
        return glm::value_ptr<float32>(mat);
    }

    const float32* toPointer(const Mat4f& mat)
    {
        return glm::value_ptr<float32>(mat);
    }

    const float32* toPointer(const Vec2f& vec)
    {
        return glm::value_ptr<float32>(vec);
    }

    const float32* toPointer(const Vec3f& vec)
    {
        return glm::value_ptr<float32>(vec);
    }

    const float32* toPointer(const Vec4f& vec)
    {
        return glm::value_ptr<float32>(vec);
    }

    const float32* toPointer(const Quatf& quat)
    {
        return glm::value_ptr<float32>(quat);
    }

    Pos lerp(const Pos& start, const Pos& end, float32 percent)
    {
        return Pos(lerp(start.pos2D(), end.pos2D(), percent), start.l);
    }

    Pos slerp(const Pos& start, const Pos& end, float32 percent)
    {
        return Pos(Easy2D::slerp(start.pos2D(), end.pos2D(), percent), start.l);
    }

    Pos nlerp(const Pos& start, const Pos& end, float32 percent)
    {
        return Pos(nlerp(start.pos2D(), end.pos2D(), percent), start.l);
    }

    float32 mag(const Pos& pos)
    {
        return Easy2D::mag(pos.pos2D());
    }

    float32 dot(const Pos& posA, const Pos& posB)
    {
        return Easy2D::dot(posA.pos2D(), posB.pos2D());
    }

    Pos mul(const Pos& position, const Mat2f& mat)
    {
        return Pos(Easy2D::mul(position.pos2D(), mat), position.l);
    }

    void mul(const Pos& posIn, const Mat2f& mat, Pos& posOut)
    {
        posOut = Pos(Easy2D::mul(posIn.pos2D(), mat), posIn.l);
    }

    Pos normalize(const Pos& position)
    {
        return Pos(Easy2D::normalize(position.pos2D()), position.l);
    }

    void normalize(const Pos& posIn, Pos& posOut)
    {
        posOut = Pos(Easy2D::normalize(posIn.pos2D()), posIn.l);
    }

    float32 distance(const Pos& posA, const Pos& posB)
    {
        return Easy2D::distance(posA.pos2D(), posB.pos2D());
    }

    Mat4f translate(const Pos& pos)
    {
        return Easy2D::translate(pos.pos3D());
    }

    Mat4f translate(const Mat4f& mat, const Pos& pos)
    {
        Vec3f pos3D(pos.pos3D());
        return Easy2D::translate(mat, pos3D);
    }

    void translate(const Pos& pos, Mat4f& out)
    {
        out = Easy2D::translate(pos.pos3D());
    }

    void translate(const Mat4f& mat, const Pos& pos, Mat4f& out)
    {
        Vec3f pos3D(pos.pos3D());
        out = Easy2D::translate(mat, pos3D);
    }

    Mat4f scale(const Pos& pos)
    {
        return Easy2D::scale(pos.pos3D());
    }

    Mat4f scale(const Mat4f& mat, const Pos& pos)
    {
        Vec3f pos3D(pos.pos3D());
        return Easy2D::scale(mat, pos3D);
    }

    void scale(const Pos& pos, Mat4f& out)
    {
        out = Easy2D::scale(pos.pos3D());
    }

    void scale(const Mat4f& mat, const Pos& pos, Mat4f& out)
    {
        Vec3f pos3D(pos.pos3D());
        out = Easy2D::scale(mat, pos3D);
    }

    Mat4f lookAt(const Pos& eye, const Pos& center)
    {
        return Easy2D::lookAt(eye.pos3D(), center.pos3D(), Vec3f(0, 0, 1.0f));
    }

    void lookAt(const Pos& eye, const Pos& center, Mat4f& out)
    {
        out = Easy2D::lookAt(eye.pos3D(), center.pos3D(), Vec3f(0, 0, 1.0f));
    }

    Pos log(const Pos& pos)
    {
        return Pos(Easy2D::log(pos.pos2D()), pos.l);
    }

    void log(const Pos& posIn, Pos& posOut)
    {
        posOut = Pos(Easy2D::log(posIn.pos2D()), posIn.l);
    }

    Pos log2(const Pos& pos)
    {
        return Pos(Easy2D::log2(pos.pos2D()), pos.l);
    }

    void log2(const Pos& posIn, Pos& posOut)
    {
        posOut = Pos(Easy2D::log2(posIn.pos2D()), posIn.l);
    }

    Pos step(const Pos& pos, const Vec2f& x)
    {
        Vec2f pos2D = pos.pos2D();
        return Pos(Easy2D::step(pos2D, x), pos.l);
    }

    Pos step(const Pos& pos, float32 x)
    {
        Vec2f pos2D = pos.pos2D();
        return Pos(Easy2D::step(pos2D, x), pos.l);
    }

    void step(const Pos& posIn, const Vec2f& x, Pos& posOut)
    {
        Vec2f pos2D = posIn.pos2D();
        posOut = Pos(Easy2D::step(pos2D, x), posIn.l);
    }

    void step(const Pos& posIn, float32 x, Pos& posOut)
    {
        Vec2f pos2D = posIn.pos2D();
        posOut = Pos(Easy2D::step(pos2D, x), posIn.l);
    }

    Pos mod(const Pos& pos, const Vec2f& mod)
    {
        Vec2f pos2D = pos.pos2D();
        return Pos(Easy2D::mod(pos2D, mod), pos.l);
    }

    Pos mod(const Pos& pos, float32 mod)
    {
        Vec2f pos2D = pos.pos2D();
        return Pos(Easy2D::mod(pos2D, mod), pos.l);
    }

    void mod(const Pos& posIn, const Vec2f& mod, Pos& posOut)
    {
        Vec2f pos2D = posIn.pos2D();
        posOut = Pos(Easy2D::mod(pos2D, mod), posIn.l);
    }

    void mod(const Pos& posIn, float32 mod, Pos& posOut)
    {
        Vec2f pos2D = posIn.pos2D();
        posOut = Pos(Easy2D::mod(pos2D, mod), posIn.l);
    }

    bool posInRect(const Vec2& leftTop, const Vec2& size, const Vec2& pos)
    {
        if ((pos.x <= (leftTop.x + size.x) && pos.x >= leftTop.x) && (pos.y <= (leftTop.y + size.y) && pos.y >= leftTop.y))
        {
            return true;
        }
        return false;
    }
   }