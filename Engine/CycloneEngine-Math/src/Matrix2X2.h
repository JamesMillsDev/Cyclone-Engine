#ifndef CYCLONE_MATH_MAT_2
#define CYCLONE_MATH_MAT_2

#include "CycloneMath.h"

namespace CycloneEngine
{
#define MATRIX_2_SIZE 2
    
    typedef struct Matrix2X2
    {
        union
        {
            struct
            {
                float m11, m12,
                    m21, m22;
            };

            float asArray[MATRIX_2_SIZE * MATRIX_2_SIZE];
        };

        inline float* operator[](const int _index)
        {
            return &asArray[_index * MATRIX_2_SIZE];
        }

        inline Matrix2X2()
        {
            m11 = m22 = 1.0f;
            m12 = m21 = 0.0f;
        }

        inline Matrix2X2(float _m11, float _m12, float _m21, float _m22)
        {
            m11 = _m11;
            m12 = _m12;
            m21 = _m21;
            m22 = _m22;
        }

        CYCLONE_DLL static Matrix2X2 Transpose(const Matrix2X2& _matrix);
        CYCLONE_DLL static Matrix2X2 Inverse(const Matrix2X2& _matrix);
        
    } Matrix2X2;

    CYCLONE_DLL Matrix2X2 operator*(const Matrix2X2& _matrix, float _scalar);
    CYCLONE_DLL Matrix2X2 operator*(const Matrix2X2& _matrix, const Matrix2X2& _other);
}

#endif