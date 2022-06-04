#ifndef CYCLONE_MATH_MAT_3
#define CYCLONE_MATH_MAT_3

#include "CycloneMath.h"

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

        CYCLONE_DLL static Matrix4X4 Transpose(const Matrix4X4& _matrix);
        
    } Matrix4X4;
}

#endif