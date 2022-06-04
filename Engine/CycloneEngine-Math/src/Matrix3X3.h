#ifndef CYCLONE_MATH_MAT_3
#define CYCLONE_MATH_MAT_3

#include "CycloneMath.h"

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

        CYCLONE_DLL static Matrix3X3 Transpose(const Matrix3X3& _matrix);
        
    } Matrix3X3;
}

#endif