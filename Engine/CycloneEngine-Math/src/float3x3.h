#ifndef CYCLONE_MATH_FLOAT_3X3
#define CYCLONE_MATH_FLOAT_3X3

#include "float3.h"

namespace CycloneEngine
{
#define FLOAT3X3_SIZE 3
    
    typedef struct float3x3
    {
        union
        {
            struct
            {
                float m11, m12, m13,
                    m21, m22, m23,
                    m31, m32, m33;
            };

            float asArray[FLOAT3X3_SIZE * FLOAT3X3_SIZE];
        };

        inline float* operator[](const int _index)
        {
            return &asArray[_index * FLOAT3X3_SIZE];
        }

        inline float3x3()
        {
            m11 = m22 = m33 = 1.0f;
            m12 = m13 = m21 = 0.0f;
            m23 = m31 = m32 = 0.0f;
        }

        inline float3x3(float _m11, float _m12, float _m13, 
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

        static float3x3 Transpose(const float3x3& _matrix);
        static float3x3 Inverse(const float3x3& _matrix);

        static float3x3 Rotation(float _pitch, float _yaw, float _roll);
        static float3x3 AxisAngle(const float3& _axis, float _angle);

        static float3 MultiplyVector(const float3& _vector, const float3x3& _matrix);
        
    } float3x3;

    float3x3 operator*(const float3x3& _matrix, float _scalar);
    float3x3 operator*(const float3x3& _matrix, const float3x3& _other);
}

#endif //!CYCLONE_MATH_FLOAT_3X3