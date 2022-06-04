#ifndef CYCLONE_MATH_MAT_2
#define CYCLONE_MATH_MAT_2
#include <sys/stat.h>

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

        CYCLONE_DLL static Matrix2X2 Transpose(const Matrix2X2& _matrix);
        
    } Matrix2X2;
}

#endif