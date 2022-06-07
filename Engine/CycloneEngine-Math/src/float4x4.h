#ifndef CYCLONE_MATH_FLOAT_4X4
#define CYCLONE_MATH_FLOAT_4X4

#include "CycloneMath.h"

#include "float3.h"

namespace CycloneEngine
{
#define FLOAT4X4_SIZE 4
    
    typedef struct float4x4
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

            float asArray[FLOAT4X4_SIZE * FLOAT4X4_SIZE];
        };

        inline float* operator[](const int _index)
        {
            return &asArray[_index * FLOAT4X4_SIZE];
        }

        inline float4x4()
        {
            m11 = m22 = m33 = m44 = 1.0f;
            m12 = m13 = m14 = m21 = 0.0f;
            m23 = m24 = m31 = m32 = 0.0f;
            m34 = m41 = m42 = m43 = 0.0f;
        }

        inline float4x4(float _m11, float _m12, float _m13, float _m14,
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

        CYCLONE_DLL static float4x4 Transpose(const float4x4& _matrix);
        CYCLONE_DLL static float4x4 Inverse(const float4x4& _matrix);

        CYCLONE_DLL static float4x4 Translation(const float _x, const float _y, const float _z);
        CYCLONE_DLL static float4x4 Translation(const float3& _pos);
        CYCLONE_DLL static float3 GetTranslation(const float4x4& _matrix);

        CYCLONE_DLL static float4x4 Scale(const float _x, const float _y, const float _z);
        CYCLONE_DLL static float4x4 Scale(const float3& _scale);
        CYCLONE_DLL static float3 GetScale(const float4x4& _matrix);

        CYCLONE_DLL static float4x4 Rotation(float _pitch, float _yaw, float _roll);
        CYCLONE_DLL static float4x4 AxisAngle(const float3& _axis, float _angle);
        
    } float4x4;

    CYCLONE_DLL float4x4 operator*(const float4x4& _matrix, float _scalar);
    CYCLONE_DLL float4x4 operator*(const float4x4& _matrix, const float4x4& _other);
}

#endif //!CYCLONE_MATH_FLOAT_4X4