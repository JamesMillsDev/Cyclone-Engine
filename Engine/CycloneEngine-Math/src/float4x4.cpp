#include "float4x4.h"

#include "Mathf.h"
#include "MatrixMath.h"

namespace CycloneEngine
{
    float4x4 float4x4::Transpose(const float4x4& _matrix)
    {
        float4x4 result;
        MatrixMath::Transpose(_matrix.asArray, result.asArray, FLOAT4X4_SIZE, FLOAT4X4_SIZE);
        return result;
    }

    float4x4 float4x4::Inverse(const float4x4& _matrix)
    {
        float det = MatrixMath::Determinant(_matrix);
        if (CMP(det, 0.0f))
            return float4x4();

        return MatrixMath::Adjugate(_matrix) * (1.0f / det);
    }

    float4x4 float4x4::Translation(const float _x, const float _y, const float _z)
    {
        return float4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _x, _y, _z, 1.0f
        );
    }

    float4x4 float4x4::Translation(const float3& _pos)
    {
        return float4x4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _pos.x, _pos.y, _pos.z, 1.0f
        );
    }

    float3 float4x4::GetTranslation(const float4x4& _matrix)
    {
        return float3(_matrix.m41, _matrix.m42, _matrix.m43);
    }

    float4x4 float4x4::Scale(const float _x, const float _y, const float _z)
    {
        return float4x4(
            _x, 0.0f, 0.0f, 0.0f,
            0.0f, _y, 0.0f, 0.0f,
            0.0f, 0.0f, _z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    float4x4 float4x4::Scale(const float3& _scale)
    {
        return float4x4(
            _scale.x, 0.0f, 0.0f, 0.0f,
            0.0f, _scale.y, 0.0f, 0.0f,
            0.0f, 0.0f, _scale.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    float3 float4x4::GetScale(const float4x4& _matrix)
    {
        return float3(_matrix.m11, _matrix.m22, _matrix.m33);
    }

    float4x4 float4x4::Rotation(float _pitch, float _yaw, float _roll)
    {
        return MatrixMath::ZRotation(_roll) *
            MatrixMath::XRotation(_pitch) *
            MatrixMath::YRotation(_yaw);
    }

    float4x4 float4x4::AxisAngle(const float3& _axis, float _angle)
    {
        _angle = DEG2RAD(_angle);
        float c = cosf(_angle);
        float s = sinf(_angle);
        float t = 1.0f - cosf(_angle);

        float x = _axis.x;
        float y = _axis.y;
        float z = _axis.z;
        if (!CMP(_axis.MagnitudeSq(), 1.0f))
        {
            float invLength = 1.0f / _axis.Magnitude();
            x *= invLength;
            y *= invLength;
            z *= invLength;
        }

        return float4x4(
            t * (x * x) + c, t * x * y + s * z, t * x * z - s * y, 0.0f,
            t * x * y - s * z, t * (y * y) + c, t * y * z + s * x, 0.0f,
            t * x * z + s * y, t * y * z + s * x, t * (z * z) + c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    float4x4 operator*(const float4x4& _matrix, float _scalar)
    {
        float4x4 result;
        for (int i = 0; i < FLOAT4X4_SIZE; ++i)
        {
            result.asArray[i] = _matrix.asArray[i] * _scalar;
        }
        return result;
    }

    float4x4 operator*(const float4x4& _matrix, const float4x4& _other)
    {
        float4x4 result;
        MatrixMath::Multiply(result.asArray, _matrix.asArray, FLOAT4X4_SIZE, FLOAT4X4_SIZE, _other.asArray, FLOAT4X4_SIZE, FLOAT4X4_SIZE);
        return result;
    }
}