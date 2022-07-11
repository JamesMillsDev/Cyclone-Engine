#ifndef CYCLONE_MATH_QUATERNION
#define CYCLONE_MATH_QUATERNION

#include "CycloneMath.h"

#include "float3.h"
#include "float3x3.h"
#include "float4x4.h"

namespace CycloneEngine
{
#define QUATERNION_SIZE 2
    
    typedef struct quaternion
    {
        union
        {
            struct
            {
                float x; // vector x component
                float y; // vector y component
                float z; // vector z component
                float w; // scalar
            };

            float asArray[QUATERNION_SIZE];
        };

        float& operator[](const int _i)
        {
            return asArray[_i];
        }

        CYCLONE_DLL quaternion();
        CYCLONE_DLL quaternion(float _x, float _y, float _z, float _w);
        CYCLONE_DLL quaternion(float3 _vector, float _scalar);
        CYCLONE_DLL quaternion(const quaternion& _value);
        CYCLONE_DLL quaternion& operator=(const quaternion& _value);
        
        CYCLONE_DLL ~quaternion();
        CYCLONE_DLL float3 Complex() const;
        CYCLONE_DLL void Complex(const float3& _vector);

        CYCLONE_DLL quaternion Conjugate() const;
        CYCLONE_DLL quaternion Inverse() const;
        
        CYCLONE_DLL quaternion Product(const quaternion& _rhs) const;
        
        CYCLONE_DLL float4x4 Matrix() const;
        CYCLONE_DLL float4x4 RightMatrix() const;
        CYCLONE_DLL float Magnitude() const;
        
        CYCLONE_DLL float3x3 RotationMatrix() const;
        CYCLONE_DLL float3 RotateVector(const float3& _vector) const;
        
        CYCLONE_DLL void EulerAngles(const float3& _vector);
        CYCLONE_DLL float3 EulerAngles() const;
        
        CYCLONE_DLL quaternion operator*(const quaternion& _rhs) const;
        CYCLONE_DLL quaternion operator*(float _scalar) const;
        CYCLONE_DLL quaternion operator+(const quaternion& _rhs) const;
        CYCLONE_DLL quaternion operator-(const quaternion& _rhs) const;
        CYCLONE_DLL quaternion operator-() const;
        CYCLONE_DLL quaternion operator/(float _scalar) const;

        CYCLONE_DLL static quaternion Slerp(const quaternion& _a, const quaternion& _b, float _t);
        CYCLONE_DLL static quaternion Euler(const float3& _vector);
    
    } quaternion;
}

#endif //!CYCLONE_MATH_QUATERNION