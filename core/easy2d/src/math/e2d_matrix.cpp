#include "e2d_matrix.h"
#include "e2d_math.h"

/* Easy2D */
using namespace Easy2D;

/* MATRIX4x4*/
static float Matrix4x4Identity[] =
{
    1.0,0.0,0.0,0.0,
    0.0,1.0,0.0,0.0,
    0.0,0.0,1.0,0.0,
    0.0,0.0,0.0,1.0
};

static float Matrix4x4Zero[] =
{
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0,
    0.0,0.0,0.0,0.0
};

Matrix4x4 Matrix4x4::IDENTITY;
Matrix4x4 Matrix4x4::ZERO(Matrix4x4Zero);

static inline bool gluInvertMatrix(const float m[16], float invOut[16])
{
    int i;
    float inv[16], det;
    inv[0] = m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15]
        + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
    inv[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15]
        - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
    inv[8] = m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15]
        + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
    inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14]
        - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
    inv[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15]
        - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
    inv[5] = m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15]
        + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
    inv[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15]
        - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
    inv[13] = m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14]
        + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
    inv[2] = m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15]
        + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
    inv[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15]
        - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
    inv[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15]
        + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
    inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14]
        - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
    inv[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11]
        - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
    inv[7] = m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11]
        + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
    inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11]
        - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
    inv[15] = m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10]
        + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

    det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
    if (det == 0)
        return false;
    det = 1.0f / det;
    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
    return true;
}

Matrix4x4::Matrix4x4()
{
    identity();
};

Matrix4x4::Matrix4x4(const Matrix4x4& m4x4)
{
    (*this) = m4x4;
}

Matrix4x4::Matrix4x4(float* m4x4)
{
    memcpy(entries, m4x4, 16 * sizeof(float));
}

Matrix4x4::Matrix4x4(float e0, float e1, float e2, float e3,
    float e4, float e5, float e6, float e7,
    float e8, float e9, float e10, float e11,
    float e12, float e13, float e14, float e15)
{
    entries[0] = e0;
    entries[1] = e1;
    entries[2] = e2;
    entries[3] = e3;
    entries[4] = e4;
    entries[5] = e5;
    entries[6] = e6;
    entries[7] = e7;
    entries[8] = e8;
    entries[9] = e9;
    entries[10] = e10;
    entries[11] = e11;
    entries[12] = e12;
    entries[13] = e13;
    entries[14] = e14;
    entries[15] = e15;
}

void Matrix4x4::identity()
{
    memcpy(entries, Matrix4x4Identity, 16 * sizeof(float));
}

void Matrix4x4::zero()
{
    memset(entries, 0, sizeof(float) * 16);
}

float Matrix4x4::getDeterminant() const
{

    float a0 = entries[0] * entries[5] - entries[1] * entries[4];
    float a1 = entries[0] * entries[6] - entries[2] * entries[4];
    float a2 = entries[0] * entries[7] - entries[3] * entries[4];
    float a3 = entries[1] * entries[6] - entries[2] * entries[5];
    float a4 = entries[1] * entries[7] - entries[3] * entries[5];
    float a5 = entries[2] * entries[7] - entries[3] * entries[6];
    float b0 = entries[8] * entries[13] - entries[9] * entries[12];
    float b1 = entries[8] * entries[14] - entries[10] * entries[12];
    float b2 = entries[8] * entries[15] - entries[11] * entries[12];
    float b3 = entries[9] * entries[14] - entries[10] * entries[13];
    float b4 = entries[9] * entries[15] - entries[11] * entries[13];
    float b5 = entries[10] * entries[15] - entries[11] * entries[14];

    // Calculate the determinant.
    return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
}

Matrix4x4 Matrix4x4::mul(const Matrix4x4& m4x4) const
{
#if defined( ENABLE_NEON )
    Matrix4x4 out_m4x4;
    NEON_Matrix4Mul(this->entries, m4x4.entries, out_m4x4.entries);
    return out_m4x4;
#elif defined( ENABLE_VFP )
    Matrix4x4 out_m4x4;
    Matrix4Mul(this->entries, m4x4.entries, out_m4x4.entries);
    return out_m4x4;
#elif defined( SIMD_SSE2 )
    Matrix4x4 out_m4x4;
    SSE2_Matrix4Mul(out_m4x4, m4x4, *this);
    return out_m4x4;
#else
    return Matrix4x4(entries[0] * m4x4.entries[0] + entries[4] * m4x4.entries[1] + entries[8] * m4x4.entries[2] + entries[12] * m4x4.entries[3],
        entries[1] * m4x4.entries[0] + entries[5] * m4x4.entries[1] + entries[9] * m4x4.entries[2] + entries[13] * m4x4.entries[3],
        entries[2] * m4x4.entries[0] + entries[6] * m4x4.entries[1] + entries[10] * m4x4.entries[2] + entries[14] * m4x4.entries[3],
        entries[3] * m4x4.entries[0] + entries[7] * m4x4.entries[1] + entries[11] * m4x4.entries[2] + entries[15] * m4x4.entries[3],
        entries[0] * m4x4.entries[4] + entries[4] * m4x4.entries[5] + entries[8] * m4x4.entries[6] + entries[12] * m4x4.entries[7],
        entries[1] * m4x4.entries[4] + entries[5] * m4x4.entries[5] + entries[9] * m4x4.entries[6] + entries[13] * m4x4.entries[7],
        entries[2] * m4x4.entries[4] + entries[6] * m4x4.entries[5] + entries[10] * m4x4.entries[6] + entries[14] * m4x4.entries[7],
        entries[3] * m4x4.entries[4] + entries[7] * m4x4.entries[5] + entries[11] * m4x4.entries[6] + entries[15] * m4x4.entries[7],
        entries[0] * m4x4.entries[8] + entries[4] * m4x4.entries[9] + entries[8] * m4x4.entries[10] + entries[12] * m4x4.entries[11],
        entries[1] * m4x4.entries[8] + entries[5] * m4x4.entries[9] + entries[9] * m4x4.entries[10] + entries[13] * m4x4.entries[11],
        entries[2] * m4x4.entries[8] + entries[6] * m4x4.entries[9] + entries[10] * m4x4.entries[10] + entries[14] * m4x4.entries[11],
        entries[3] * m4x4.entries[8] + entries[7] * m4x4.entries[9] + entries[11] * m4x4.entries[10] + entries[15] * m4x4.entries[11],
        entries[0] * m4x4.entries[12] + entries[4] * m4x4.entries[13] + entries[8] * m4x4.entries[14] + entries[12] * m4x4.entries[15],
        entries[1] * m4x4.entries[12] + entries[5] * m4x4.entries[13] + entries[9] * m4x4.entries[14] + entries[13] * m4x4.entries[15],
        entries[2] * m4x4.entries[12] + entries[6] * m4x4.entries[13] + entries[10] * m4x4.entries[14] + entries[14] * m4x4.entries[15],
        entries[3] * m4x4.entries[12] + entries[7] * m4x4.entries[13] + entries[11] * m4x4.entries[14] + entries[15] * m4x4.entries[15]);

#endif
}

Matrix4x4 Matrix4x4::mul2D(const Matrix4x4& m4x4) const
{
#if defined( ENABLE_NEON )
    Matrix4x4 out_m4x4;
    NEON_Matrix4Mul(this->entries, m4x4.entries, out_m4x4.entries);
    return out_m4x4;
#elif defined( ENABLE_VFP )
    Matrix4x4 out_m4x4;
    Matrix4Mul(this->entries, m4x4.entries, out_m4x4.entries);
    return out_m4x4;
#elif defined( SIMD_SSE2 )
    Matrix4x4 out_m4x4;
    SSE2_Matrix4Mul(out_m4x4, m4x4, *this);
    return out_m4x4;
#else
    /*

    | (0)  (1)  0 |   | (0)  (1)  0 |
    | (4)  (5)  0 | x | (4)  (5)  0 |
    | (12) (13) 1 |   | (12) (13) 1 |

    (0)  = (0)*(0)+(1)*(4)           (+0*(12))
    (1)  = (0)*(1)+(1)*(5)           (+0*(13))
     0   = 0
    (4)  = (4)*(0)+(5)*(4)           (+0*(12))
    (5)  = (4)*(1)+(5)*(5)           (+0*(13))
     0   = 0
    (12) = (12)*(0)+(13)*(4)+1*(12)
    (13) = (12)*(1)+(13)*(5)+1*(13)
     1   = 1
    */
    return Matrix4x4(
        entries[0] * m4x4.entries[0] + entries[4] * m4x4.entries[1],
        entries[1] * m4x4.entries[0] + entries[5] * m4x4.entries[1],
        0,
        0,
        //
        entries[0] * m4x4.entries[4] + entries[4] * m4x4.entries[5],
        entries[1] * m4x4.entries[4] + entries[5] * m4x4.entries[5],
        0,
        0,
        //
        0,
        0,
        1,
        0,
        //
        entries[0] * m4x4.entries[12] + entries[4] * m4x4.entries[13] + entries[12],
        entries[1] * m4x4.entries[12] + entries[5] * m4x4.entries[13] + entries[13],
        0,
        1);
#endif
}

Vector4D Matrix4x4::mul(const Vector4D& v4) const
{
    Vector4D out;
#if defined( ENABLE_NEON )
    NEON_Matrix4Vector4Mul(this->entries, &v4.x, &out.x);
#elif defined( ENABLE_VFP )
    Matrix4Vector4Mul(this->entries, &v4.x, &out.x);
#elif defined( SIMD_SSE2 )
    out.row = SSE2_lincomb(v4.row, *this);
#else
    out.x = entries[0] * v4.x + entries[4] * v4.y + entries[8] * v4.z + entries[12] * v4.w;
    out.y = entries[1] * v4.x + entries[5] * v4.y + entries[9] * v4.z + entries[13] * v4.w;
    out.z = entries[2] * v4.x + entries[6] * v4.y + entries[10] * v4.z + entries[14] * v4.w;
    out.w = entries[3] * v4.x + entries[7] * v4.y + entries[11] * v4.z + entries[15] * v4.w;
#endif
    return out;
}

Vector2D Matrix4x4::mul2D(const Vector2D& v2) const
{
    Vector2D out;
    out.x = entries[0] * v2.x + entries[4] * v2.y + entries[8] + entries[12];
    out.y = entries[1] * v2.x + entries[5] * v2.y + entries[9] + entries[13];
    return out;
}

void Matrix4x4::inverse()
{
#if defined( SIMD_SSE2 )
    SSE2_Matrix4Inv(*this);
#else
    gluInvertMatrix(&(this->entries[0]), &(this->entries[0]));
#endif
}

void Matrix4x4::inverse2D()
{
    float det = entries[0] * entries[5] - entries[1] * entries[4];
    float tmp_entries_0 = entries[0];
    entries[0] = entries[5] / det;
    entries[1] = -entries[1] / det;
    entries[4] = -entries[4] / det;
    entries[5] = tmp_entries_0 / det;

    entries[12] = (-(entries[0] * entries[12])) - entries[4] * entries[13];
    entries[13] = (-(entries[1] * entries[12])) - entries[5] * entries[13];
}

Matrix4x4 Matrix4x4::getInverse() const
{
#if defined( SIMD_SSE2 )
    Matrix4x4 out(*this);
    SSE2_Matrix4Inv(out);
#else
    Matrix4x4 out;
    gluInvertMatrix(&(entries[0]), &(out.entries[0]));
#endif
    return out;
}

Matrix4x4 Matrix4x4::getInverse2D() const
{
    ///@code
    /// INVERSE ROTATION / SCALE
    ///      | a b |                   | a b | T (T does not mean transposed matrix)
    ///  A=  | c d |   A^-1 = 1/det(A) | c d |
    ///
    ///                   |  d -b |
    ///  A^-1 = 1/det(A)  | -c  a |
    ///  det(A) = a*d-b*c
    ///  invdet= 1/ (a*d-b*c)
    ///
    /// a=(0), b=(1)
    /// c=(4), d=(5)
    ///
    ///  det(A) = (0)*(5)-(1)*(4)
    ///  (0)=   (5) / det(A)
    ///  (1)=  -(1) / det(A)
    ///  (4)=  -(4) / det(A)
    ///  (5)=   (0) / det(A)
    ///
    ///@endcode
    Matrix4x4 out;
    float det = entries[0] * entries[5] - entries[1] * entries[4];

    out.entries[0] = entries[5] / det;
    out.entries[1] = -entries[1] / det;
    out.entries[4] = -entries[4] / det;
    out.entries[5] = entries[0] / det;
    ///@code
    ///INVERSE TRANSLATION
    ///
    /// MULL -t X R^1
    /// |  I    0    |    | R^-1     0 |
    /// | -t    I    |  x |   0      I | =
    ///
    /// | I*R^-1     0 |   |  R^-1      0 |
    /// | (-t)*R^-1  I | = | (-t)*R^-1  I |
    ///
    /// (-t)*R^-1
    ///
    ///  t=[ x y ] -> -t =[ -x -y ]
    ///
    ///  [ -x -y ] x | a b |
    ///              | c d | =
    ///
    ///
    /// (-t)*R^-1 = [ (-(a*x))-c*y  (-(b*x))-d*y ]
    ///
    /// x=entries[12];
    /// y=entries[13];
    ///
    ///  out : = R^-1
    ///
    /// a=out.entries[0];
    /// b=out.entries[1];
    /// c=out.entries[4];
    /// d=out.entries[5];
    ///
    /// out.entries[12]= (-(a*x))-c*y
    /// out.entries[13]= (-(b*x))-d*y
    ///
    /// then....
    /// out.entries[12]= (-(out.entries[0]*entries[12]))-out.entries[4]*entries[13];
    /// out.entries[13]= (-(out.entries[1]*entries[12]))-out.entries[5]*entries[13];
    ///@endcode
    ////////////////////////////////////////////
    out.entries[12] = (-(out.entries[0] * entries[12])) - out.entries[4] * entries[13];
    out.entries[13] = (-(out.entries[1] * entries[12])) - out.entries[5] * entries[13];
    return out;
}

Matrix4x4 Matrix4x4::getTranspose() const
{
#if defined( SIMD_SSE2 )
    Matrix4x4 newMat(*this);
    SSE2_Matrix4Transpose(newMat);
    return newMat;
#else
    Matrix4x4 newMat(*this);
    float tmp;

#define _xy_m4x4_(x,y) newMat.entries[(y*4)+x]

    tmp = _xy_m4x4_(1, 0);
    _xy_m4x4_(1, 0) = _xy_m4x4_(0, 1);
    _xy_m4x4_(0, 1) = tmp;

    tmp = _xy_m4x4_(2, 0);
    _xy_m4x4_(2, 0) = _xy_m4x4_(0, 2);
    _xy_m4x4_(0, 2) = tmp;

    tmp = _xy_m4x4_(2, 1);
    _xy_m4x4_(2, 1) = _xy_m4x4_(1, 2);
    _xy_m4x4_(1, 2) = tmp;

    tmp = _xy_m4x4_(3, 0);
    _xy_m4x4_(3, 0) = _xy_m4x4_(0, 3);
    _xy_m4x4_(0, 3) = tmp;

    tmp = _xy_m4x4_(3, 1);
    _xy_m4x4_(3, 1) = _xy_m4x4_(1, 3);
    _xy_m4x4_(1, 3) = tmp;

    tmp = _xy_m4x4_(3, 2);
    _xy_m4x4_(3, 2) = _xy_m4x4_(2, 3);
    _xy_m4x4_(2, 3) = tmp;

#undef _xy_m4x4_

    return newMat;
#endif
}

///set scale
void Matrix4x4::setScale(const Vector3D& v3)
{
    identity();
    entries[0] = v3.x;
    entries[5] = v3.y;
    entries[10] = v3.z;
}

void Matrix4x4::setScale(const Vector2D& v2)
{
    identity();
    entries[0] = v2.x;
    entries[5] = v2.y;
}

///force scale trasformation
void Matrix4x4::unsafeScale(const Vector3D& v3)
{
    entries[0] = v3.x;
    entries[5] = v3.y;
    entries[10] = v3.z;
}

void Matrix4x4::unsafeScale(const Vector2D& v2)
{
    entries[0] = v2.x;
    entries[5] = v2.y;
}

///concatenate trasformation
void Matrix4x4::addScale(const Vector3D& v3)
{
    entries[0] *= v3.x;
    entries[1] *= v3.y;
    entries[2] *= v3.z;
    entries[4] *= v3.x;
    entries[5] *= v3.y;
    entries[6] *= v3.z;
    entries[8] *= v3.x;
    entries[9] *= v3.y;
    entries[10] *= v3.z;
}

void Matrix4x4::addScale(const Vector2D& v2)
{
    entries[0] *= v2.x;
    entries[1] *= v2.y;
    entries[4] *= v2.x;
    entries[5] *= v2.y;
    entries[8] *= v2.x;
    entries[9] *= v2.y;
}

///return scale
Vector3D Matrix4x4::getScale3D() const
{
    return Vec3(Vec3(entries[0], entries[4], entries[8]).length(),
        Vec3(entries[1], entries[5], entries[9]).length(),
        Vec3(entries[2], entries[6], entries[10]).length());
}

Vector2D Matrix4x4::getScale2D() const
{
    return Vec2(Vec2(entries[0], entries[4]).length(),
        Vec2(entries[1], entries[5]).length());
}

//set translation
void Matrix4x4::setTranslation(const Vector3D& v3)
{
    identity();
    entries[12] = v3.x;
    entries[13] = v3.y;
    entries[14] = v3.z;
}

void Matrix4x4::setTranslation(const Vector2D& v2)
{
    identity();
    entries[12] = v2.x;
    entries[13] = v2.y;
}

///force translation translation
void Matrix4x4::unsafeTranslation(const Vector3D& v3)
{
    entries[12] = v3.x;
    entries[13] = v3.y;
    entries[14] = v3.z;
}

void Matrix4x4::unsafeTranslation(const Vector2D& v2)
{
    entries[12] = v2.x;
    entries[13] = v2.y;
}

///return translation
Vector3D Matrix4x4::getTranslation3D() const
{
    return Vector3D(entries[12], entries[13], entries[14]);
}

Vector2D Matrix4x4::getTranslation2D() const
{
    return Vector2D(entries[12], entries[13]);
}

///set concatenate trasformation:
void Matrix4x4::addTranslation(const Vector3D& v3)
{
    addTranslationOnX(v3.x);
    addTranslationOnY(v3.y);
    addTranslationOnZ(v3.z);
}

void Matrix4x4::addTranslation(const Vector2D& v2)
{
    addTranslationOnX(v2.x);
    addTranslationOnY(v2.y);
}

void Matrix4x4::addTranslationOnX(float distance)
{
    entries[0] = entries[0] + distance * entries[3];
    entries[4] = entries[4] + distance * entries[7];
    entries[8] = entries[8] + distance * entries[11];
    entries[12] = entries[12] + distance * entries[15];
}

void Matrix4x4::addTranslationOnY(float distance)
{
    entries[1] = entries[1] + distance * entries[3];
    entries[5] = entries[5] + distance * entries[7];
    entries[9] = entries[9] + distance * entries[11];
    entries[13] = entries[13] + distance * entries[15];
}

void Matrix4x4::addTranslationOnZ(float distance)
{
    entries[2] = entries[2] + distance * entries[3];
    entries[6] = entries[6] + distance * entries[7];
    entries[10] = entries[10] + distance * entries[11];
    entries[14] = entries[14] + distance * entries[15];
}

///add a euler rotarion
void Matrix4x4::addEulerRotation(const Vec3& euler)
{
    //var dec
    float cos_ang, sin_ang;
    // yaw
    cos_ang = std::cos(euler.y);
    sin_ang = std::sin(euler.y);

    float m00 = entries[0] * cos_ang + entries[2] * -sin_ang;
    float m01 = entries[4] * cos_ang + entries[6] * -sin_ang;
    float m02 = entries[8] * cos_ang + entries[10] * -sin_ang;

    entries[2] = entries[0] * sin_ang + entries[2] * cos_ang;
    entries[6] = entries[4] * sin_ang + entries[6] * cos_ang;
    entries[10] = entries[8] * sin_ang + entries[10] * cos_ang;

    entries[0] = m00;
    entries[4] = m01;
    entries[8] = m02;

    // pitch
    cos_ang = std::cos(euler.x);
    sin_ang = std::sin(euler.x);

    float m10 = entries[1] * cos_ang + entries[2] * sin_ang;
    float m11 = entries[5] * cos_ang + entries[6] * sin_ang;
    float m12 = entries[9] * cos_ang + entries[10] * sin_ang;

    entries[2] = entries[1] * -sin_ang + entries[2] * cos_ang;
    entries[6] = entries[5] * -sin_ang + entries[6] * cos_ang;
    entries[10] = entries[9] * -sin_ang + entries[10] * cos_ang;

    entries[1] = m10;
    entries[5] = m11;
    entries[9] = m12;

    // roll
    cos_ang = std::cos(euler.z);
    sin_ang = std::sin(euler.z);

    m00 = entries[0] * cos_ang + entries[1] * sin_ang;
    m01 = entries[4] * cos_ang + entries[5] * sin_ang;
    m02 = entries[8] * cos_ang + entries[9] * sin_ang;

    entries[1] = entries[0] * -sin_ang + entries[1] * cos_ang;
    entries[5] = entries[4] * -sin_ang + entries[5] * cos_ang;
    entries[9] = entries[8] * -sin_ang + entries[9] * cos_ang;

    entries[0] = m00;
    entries[4] = m01;
    entries[8] = m02;
}

void Matrix4x4::setRotY(Angle angle)
{
    identity();

    entries[0] = Math::cos(angle);
    entries[2] = -Math::sin(angle);

    entries[8] = -entries[2];
    entries[10] = entries[0];
}

void Matrix4x4::setRotX(Angle angle)
{
    identity();

    entries[5] = Math::cos(angle);
    entries[6] = Math::sin(angle);

    entries[9] = -entries[6];
    entries[10] = entries[5];
}

void Matrix4x4::setRotZ(Angle angle)
{
    identity();

    entries[0] = Math::cos(angle);
    entries[1] = Math::sin(angle);

    entries[4] = -entries[1];
    entries[5] = entries[0];
}

Angle Matrix4x4::getRotY() const
{
    float a = entries[8];
    float b = entries[10];
    //if(a<=0.0001 && a>=-0.0001) a=0;
    //if(b<=0.0001 && b>=-0.0001) b=0;
    return Radian(std::atan2(a, b));
}
Angle Matrix4x4::getRotX() const
{
    float ang = std::atan2(entries[9], std::sqrt(entries[8] * entries[8] + entries[10] * entries[10]));
    //if(ang<=0.0001 && ang>=-0.0001) ang=0;
    return Radian(ang);
}

Angle Matrix4x4::getRotZ() const
{
    float a = entries[0];
    float b = entries[1];
    //if(a<=0.00001 && a>=-0.00001) a=0.0;
    //if(b<=0.00001 && b>=-0.00001) b=0.0;
    return Radian(std::atan2(b, a));
}

Vec3 Matrix4x4::getRotation() const
{
    Vec3 r;
    r.x = std::asin(m12);
    if (cos(r.x) != 0.f)
    {
        r.y = std::atan2(-m02, m22);
        r.z = std::atan2(-m10, m11);
    }
    else
    {
        r.y = 0.f;
        r.z = std::atan2(m01, m00);
    }
    return r;
}

// x,y | alpha | sx,sy
void Matrix4x4::setTransform2D(const Transform2D& t2d)
{
    //(scale z=0 and Translation z=0)
    //Translation
    entries[12] = t2d.position.x;
    entries[13] = t2d.position.y;
    //RotZ
    entries[0] = Math::cos(t2d.alpha);
    entries[1] = Math::sin(t2d.alpha);
    entries[4] = -entries[1];
    entries[5] = entries[0];
    //mT x mRZ x scale
    // scale.x  // row0 * x
    entries[0] *= t2d.scale.x;
    entries[1] *= t2d.scale.x;
    // scale.y  // row1 * y
    entries[4] *= t2d.scale.y;
    entries[5] *= t2d.scale.y;
    // scale.z //
    entries[10] = 1.0f;
}

void Matrix4x4::setOrtho(float left, float right, float bottom, float top, float n, float f)
{
    identity();
    entries[0] = 2.0f / (right - left);
    entries[5] = 2.0f / (top - bottom);
    entries[10] = -2.0f / (f - n);
    entries[12] = -(right + left) / (right - left);
    entries[13] = -(top + bottom) / (top - bottom);
    entries[14] = -(f + n) / (f - n);
}

void Matrix4x4::setPerspective(float l, float r, float b, float t, float n, float f)
{
    //http://www.manpagez.com/man/3/glFrustum/
    identity();
    //row1
    entries[0] = 2 * n / (r - l);
    entries[2] = (r + l) / (r - l);
    //row2
    entries[5] = 2 * n / (t - b);
    entries[6] = (t + b) / (t - b);
    //row3
    entries[10] = -(f + n) / (f - n);
    entries[11] = -(2 * f * n) / (f - n);
    //row4
    entries[14] = -1;
    entries[15] = 0;
}

void Matrix4x4::setPerspective(float fov, float fRealAspect, float fNear, float fFar)
{
    //from:https://code.google.com/p/oolongengine/source/browse/trunk/Oolong%20Engine2/Math/Matrix.cpp
    float f, n;
    f = 1.0f / (float)std::tan(fov * 0.5f);
    n = 1.0f / (fNear - fFar);

    entries[0] = f / fRealAspect;
    entries[1] = 0;
    entries[2] = 0;
    entries[3] = 0;

    entries[4] = 0;
    entries[5] = f;
    entries[6] = 0;
    entries[7] = 0;

    entries[8] = 0;
    entries[9] = 0;
    entries[10] = (fFar + fNear) * n;
    entries[11] = -1;

    entries[12] = 0;
    entries[13] = 0;
    entries[14] = (2 * fFar * fNear) * n;
    entries[15] = 0;
}

String Matrix4x4::toString(const String& start, const String& sep, const String& sepline, const String& end) const
{
    return 	start + std::to_string(entries[0]) + sep + std::to_string(entries[1]) + sep + std::to_string(entries[2]) + sep + std::to_string(entries[3]) + sepline
        + std::to_string(entries[4]) + sep + std::to_string(entries[5]) + sep + std::to_string(entries[6]) + sep + std::to_string(entries[7]) + sepline
        + std::to_string(entries[8]) + sep + std::to_string(entries[9]) + sep + std::to_string(entries[10]) + sep + std::to_string(entries[11]) + sepline
        + std::to_string(entries[12]) + sep + std::to_string(entries[13]) + sep + std::to_string(entries[14]) + sep + std::to_string(entries[15]) + end;
}
