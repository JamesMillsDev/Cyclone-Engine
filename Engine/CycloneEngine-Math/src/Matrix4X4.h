#ifndef CYCLONE_MATH_MAT_4
#define CYCLONE_MATH_MAT_4

#include "CycloneMath.h"

#include "Vector3.h"

namespace CycloneEngine
{
#define MATRIX_4_SIZE 4
    
    typedef struct Matrix4X4
    {
        union
        {
            struct
            {
                float m11, m12, m13, m14,
                    m21, m22, m23, m24,
                    m31, m32, m33, m34,
                    m41, m42, m43, m44;
            };

            float asArray[MATRIX_4_SIZE * MATRIX_4_SIZE];
        };

        inline float* operator[](const int _index)
        {
            return &asArray[_index * MATRIX_4_SIZE];
        }

        inline Matrix4X4()
        {
            m11 = m22 = m33 = m44 = 1.0f;
            m12 = m13 = m14 = m21 = 0.0f;
            m23 = m24 = m31 = m32 = 0.0f;
            m34 = m41 = m42 = m43 = 0.0f;
        }

        inline Matrix4X4(float _m11, float _m12, float _m13, float _m14,
            float _m21, float _m22, float _m23, float _m24,
            float _m31, float _m32, float _m33, float _m34,
            float _m41, float _m42, float _m43, float _m44)
        {
            m11 = _m11;
            m12 = _m12;
            m13 = _m13;
            m14 = _m14;
            m21 = _m21;
            m22 = _m22;
            m23 = _m23;
            m24 = _m24;
            m31 = _m31;
            m32 = _m32;
            m33 = _m33;
            m34 = _m34;
            m41 = _m41;
            m42 = _m42;
            m43 = _m43;
            m44 = _m44;
        }

        CYCLONE_DLL static Matrix4X4 Transpose(const Matrix4X4& _matrix);
        CYCLONE_DLL static Matrix4X4 Inverse(const Matrix4X4& _matrix);

        CYCLONE_DLL static Matrix4X4 Translation(const float _x, const float _y, const float _z);
        CYCLONE_DLL static Matrix4X4 Translation(const Vector3& _pos);
        CYCLONE_DLL static Vector3 GetTranslation(const Matrix4X4& _matrix);

        CYCLONE_DLL static Matrix4X4 Scale(const float _x, const float _y, const float _z);
        CYCLONE_DLL static Matrix4X4 Scale(const Vector3& _scale);
        CYCLONE_DLL static Vector3 GetScale(const Matrix4X4& _matrix);

        CYCLONE_DLL static Matrix4X4 Rotation(float _pitch, float _yaw, float _roll);
        CYCLONE_DLL static Matrix4X4 AxisAngle(const Vector3& _axis, float _angle);
        
    } Matrix4X4;

    CYCLONE_DLL Matrix4X4 operator*(const Matrix4X4& _matrix, float _scalar);
    CYCLONE_DLL Matrix4X4 operator*(const Matrix4X4& _matrix, const Matrix4X4& _other);
}

#endif