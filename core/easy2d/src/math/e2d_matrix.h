#ifndef MATRIX_H
#define MATRIX_H

#include "e2d_vector4d.h"

namespace Easy2D
{
    struct Transform2D
    {
        Transform2D() :alpha(Radian(0)), scale(1.0f, 1.0f)
        {
        }

        Transform2D(const Vector2D& position, Angle alpha, const Vector2D& scale)
            :position(position), alpha(alpha), scale(scale)
        {
        }

        //values
        Vector2D position;
        Angle    alpha;
        Vector2D scale;
        //operator
        bool operator==(const Transform2D& t2d) const
        {
            return alpha == t2d.alpha && position == t2d.position && scale == t2d.scale;
        }
        bool operator!=(const Transform2D& t2d) const
        {
            return alpha != t2d.alpha || position != t2d.position || scale != t2d.scale;
        }
        //cast
        operator float* ()
        {
            return &position.x;
        }
        operator const float* () const
        {
            return &position.x;
        }
    };

    class Matrix4x4
    {
    public:
        union
        {
            float entries[16];
            struct
            {
                float m00, m01, m02, m03;
                float m10, m11, m12, m13;
                float m20, m21, m22, m23;
                float m30, m31, m32, m33;
            };
        };
        //statics
        static Matrix4x4 IDENTITY;
        static Matrix4x4 ZERO;
        //constructors
        Matrix4x4();
        Matrix4x4(const Matrix4x4& m4x4);
        Matrix4x4(float* m4x4);
        Matrix4x4(float e0, float e1, float e2, float e3,
            float e4, float e5, float e6, float e7,
            float e8, float e9, float e10, float e11,
            float e12, float e13, float e14, float e15);
        //destructor
        virtual ~Matrix4x4() {};
        ///identity
        void identity();
        ///set all values to 0
        void zero();
        ///matrix  inverse
        void inverse();
        ///matrix inverse (only 2D transformation)
        void inverse2D();
        //get matrix determinant
        float getDeterminant() const;
        ///matrix multiplication
        Matrix4x4 mul(const Matrix4x4& m4x4) const;
        ///matrix multiplication (only 2D transformation)
        Matrix4x4 mul2D(const Matrix4x4& m4x4) const;
        ///matrix * vector
        Vector4D mul(const Vector4D& v4) const;
        ///matrix * vector (only 2D transformation)
        Vector2D mul2D(const Vector2D& v2) const;
        ///return matrix inverse
        Matrix4x4 getInverse() const;
        ///return matrix inverse (only 2D transformation)
        Matrix4x4 getInverse2D() const;
        ///return matrix transposition
        Matrix4x4 getTranspose() const;
        ///set scale
        void setScale(const Vector3D& v3);
        void setScale(const Vector2D& v2);
        ///concatenate trasformation
        void addScale(const Vector3D& v3);
        void addScale(const Vector2D& v2);
        ///force scale trasformation
        void unsafeScale(const Vector3D& v3);
        void unsafeScale(const Vector2D& v2);
        ///return scale
        Vector3D getScale3D() const;
        Vector2D getScale2D() const;
        ///set translation
        void setTranslation(const Vector3D& v3);
        void setTranslation(const Vector2D& v2);
        ///concatenate trasformation
        void addTranslation(const Vector3D& v3);
        void addTranslation(const Vector2D& v2);
        void addTranslationOnX(float distance);
        void addTranslationOnY(float distance);
        void addTranslationOnZ(float distance);
        ///force translation translation
        void unsafeTranslation(const Vector3D& v3);
        void unsafeTranslation(const Vector2D& v2);
        ///return translation
        Vector3D getTranslation3D() const;
        Vector2D getTranslation2D() const;
        ///add a euler rotarion
        void addEulerRotation(const Vec3& euler);
        ///set pitch
        void setRotX(Angle x);
        ///set yaw
        void setRotY(Angle y);
        ///set roll
        void setRotZ(Angle z);
        ///return pitch
        Angle getRotX() const;
        ///return yaw
        Angle getRotY() const;
        ///return roll
        Angle getRotZ() const;
        ///rotation
        Vec3  getRotation() const;
        ///add a tranform
        void setTransform2D(const Transform2D& t2d);
        ///set orthogonal transformation (projection matrix)
        void setOrtho(float left, float right, float bottom, float top, float n, float f);
        ///set projection transformation (projection matrix)
        void setPerspective(float left, float right, float bottom, float top, float n, float f);
        void setPerspective(float fovy, float aspect, float n, float f);
        //operators:
        inline float& operator[](int i)
        {
            return entries[i];
        }
        inline float& operator()(int x, int y)
        {
            return entries[x + (y * 4)];
        }
        inline float operator[](int i) const
        {
            return entries[i];
        }
        inline float operator()(int x, int y) const
        {
            return entries[x + (y * 4)];
        }
        //
        operator float* ()
        {
            return (float*)entries;
        }
        operator const float* () const
        {
            return (const float*)entries;
        }
        //-----------------------------------------------
        String toString(const String& start = "(", const String& sep = " ", const String& sepline = " ", const String& end = ")\n") const;
    };

    //typedef
    //-----------------------------------------------
    typedef Matrix4x4 Mat4;
}

#endif
