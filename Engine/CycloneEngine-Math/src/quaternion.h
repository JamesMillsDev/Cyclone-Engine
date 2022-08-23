#ifndef CYCLONE_MATH_QUATERNION
#define CYCLONE_MATH_QUATERNION

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

        quaternion();
        quaternion(float _x, float _y, float _z, float _w);
        quaternion(float3 _vector, float _scalar);
        quaternion(const quaternion& _value);
        quaternion& operator=(const quaternion& _value);
        
        ~quaternion();
        float3 Complex() const;
        void Complex(const float3& _vector);

        quaternion Conjugate() const;
        quaternion Inverse() const;
        
        quaternion Product(const quaternion& _rhs) const;
        
        float4x4 Matrix() const;
        float4x4 RightMatrix() const;
        float Magnitude() const;
        
        float3x3 RotationMatrix() const;
        float3 RotateVector(const float3& _vector) const;
        
        void EulerAngles(const float3& _vector);
        float3 EulerAngles() const;
        
        quaternion operator*(const quaternion& _rhs) const;
        quaternion operator*(float _scalar) const;
        quaternion operator+(const quaternion& _rhs) const;
        quaternion operator-(const quaternion& _rhs) const;
        quaternion operator-() const;
        quaternion operator/(float _scalar) const;

        static quaternion Slerp(const quaternion& _a, const quaternion& _b, float _t);
        static quaternion Euler(const float3& _vector);
    
    } quaternion;
}

#endif //!CYCLONE_MATH_QUATERNION