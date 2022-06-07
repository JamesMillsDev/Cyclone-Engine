#ifndef CYCLONE_MATH_MAT_3
#define CYCLONE_MATH_MAT_3

#include "CycloneMath.h"

#include "Vector3.h"

namespace CycloneEngine
{
#define MATRIX_3_SIZE 3
    
    typedef struct Matrix3X3
    {
        union
        {
            struct
            {
                float m11, m12, m13,
                    m21, m22, m23,
                    m31, m32, m33;
            };

            float asArray[MATRIX_3_SIZE * MATRIX_3_SIZE];
        };

        inline float* operator[](const int _index)
        {
            return &asArray[_index * MATRIX_3_SIZE];
        }

        inline Matrix3X3()
        {
            m11 = m22 = m33 = 1.0f;
            m12 = m13 = m21 = 0.0f;
            m23 = m31 = m32 = 0.0f;
        }

        inline Matrix3X3(float _m11, float _m12, float _m13, 
                        float _m21, float _m22, float _m23, 
                        float _m31, float _m32, float _m33)
        {
            m11 = _m11;
            m12 = _m12;
            m13 = _m13;
            m21 = _m21;
            m22 = _m22;
            m23 = _m23;
            m31 = _m31;
            m32 = _m32;
            m33 = _m33;
        }

        CYCLONE_DLL static Matrix3X3 Transpose(const Matrix3X3& _matrix);
        CYCLONE_DLL static Matrix3X3 Inverse(const Matrix3X3& _matrix);

        CYCLONE_DLL static Matrix3X3 Rotation(float _pitch, float _yaw, float _roll);
        CYCLONE_DLL static Matrix3X3 AxisAngle(const Vector3& _axis, float _angle);
        
    } Matrix3X3;

    CYCLONE_DLL Matrix3X3 operator*(const Matrix3X3& _matrix, float _scalar);
    CYCLONE_DLL Matrix3X3 operator*(const Matrix3X3& _matrix, const Matrix3X3& _other);
}

#endif