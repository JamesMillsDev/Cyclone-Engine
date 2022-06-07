#ifndef CYCLONE_MATH_FLOAT2X2
#define CYCLONE_MATH_FLOAT2X2

#include "CycloneMath.h"

namespace CycloneEngine
{
#define FLOAT2X2_SIZE 2
    
    typedef struct float2x2
    {
        union
        {
            struct
            {
                float m11, m12,
                    m21, m22;
            };

            float asArray[FLOAT2X2_SIZE * FLOAT2X2_SIZE];
        };

        inline float* operator[](const int _index)
        {
            return &asArray[_index * FLOAT2X2_SIZE];
        }

        inline float2x2()
        {
            m11 = m22 = 1.0f;
            m12 = m21 = 0.0f;
        }

        inline float2x2(float _m11, float _m12, float _m21, float _m22)
        {
            m11 = _m11;
            m12 = _m12;
            m21 = _m21;
            m22 = _m22;
        }

        CYCLONE_DLL static float2x2 Transpose(const float2x2& _matrix);
        CYCLONE_DLL static float2x2 Inverse(const float2x2& _matrix);
        
    } float2x2;

    CYCLONE_DLL float2x2 operator*(const float2x2& _matrix, float _scalar);
    CYCLONE_DLL float2x2 operator*(const float2x2& _matrix, const float2x2& _other);
}

#endif //!CYCLONE_MATH_FLOAT2X2