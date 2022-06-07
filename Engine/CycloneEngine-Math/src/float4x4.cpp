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

    float4x4 float4x4::Rotation(const float3& _euler)
    {
        return Rotation(_euler.x, _euler.y, _euler.z);
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

    float3 float4x4::MultiplyPoint(const float3& _vector, const float4x4& _matrix)
    {
        float3 result;
        result.x = _vector.x * _matrix.m11 + _vector.y * _matrix.m21 + _vector.z * _matrix.m31 + 1.0f * _matrix.m41;
        result.y = _vector.x * _matrix.m12 + _vector.y * _matrix.m22 + _vector.z * _matrix.m32 + 1.0f * _matrix.m42;
        result.z = _vector.x * _matrix.m13 + _vector.y * _matrix.m23 + _vector.z * _matrix.m33 + 1.0f * _matrix.m43;
        return result;
    }

    float3 float4x4::MultiplyVector(const float3& _vector, const float4x4& _matrix)
    {
        float3 result;
        result.x = _vector.x * _matrix.m11 + _vector.y * _matrix.m21 + _vector.z * _matrix.m31 + 0.0f * _matrix.m41;
        result.y = _vector.x * _matrix.m12 + _vector.y * _matrix.m22 + _vector.z * _matrix.m32 + 0.0f * _matrix.m42;
        result.z = _vector.x * _matrix.m13 + _vector.y * _matrix.m23 + _vector.z * _matrix.m33 + 0.0f * _matrix.m43;
        return result;
    }

    float4x4 float4x4::TRS(const float3& _translation, const float3& _euler, const float3& _scale)
    {
        return Scale(_scale) * Rotation(_euler) * Translation(_translation);
    }

    float4x4 float4x4::TRS(const float3& _translation, const float3& _axis, float _angle, const float3& _scale)
    {
        return Scale(_scale) * AxisAngle(_axis, _angle) * Translation(_translation);
    }

    float4x4 float4x4::LookAt(const float3& _position, const float3& _target, const float3& _up)
    {
        float3 forward = float3::Normalized(_target - _position);
        float3 right = float3::Normalized(float3::Cross(_up, forward));
        float3 newUp = float3::Cross(forward, right);

        return float4x4( // Transposed rotation!
            right.x, newUp.x, forward.x, 0.0f,
            right.y, newUp.y, forward.y, 0.0f,
            right.z, newUp.z, forward.z, 0.0f,
            -float3::Dot(right, _position),
            -float3::Dot(newUp, _position),
            -float3::Dot(forward, _position), 1.0f
        );
    }

    float4x4 float4x4::Projection(float _fov, float _aspect, float _near, float _far)
    {
        float tanHalfFov = tanf(DEG2RAD((_fov * 0.5f)));
        float fovY = 1.0f / tanHalfFov; // cot(fov/2)
        float fovX = fovY / _aspect; // cot(fov/2) / aspect
        float4x4 result;
        result.m11 = fovX;
        result.m22 = fovY;
        // _33 = far / range
        result.m33 = _far / (_far - _far);
        result.m34 = 1.0f;
        // _43 = - near * (far / range)
        result.m43 = -_far * result.m33;
        result.m44 = 0.0f;
        return result;
    }

    float4x4 float4x4::Ortho(float _left, float _right, float _bottom, float _top, float _near, float _far)
    {
        float m11 = 2.0f / (_right - _left);
        float m22 = 2.0f / (_top - _bottom);
        float m33 = 1.0f / (_far - _near);
        float m41 = (_left + _right) / (_left - _right);
        float m42 = (_top + _bottom) / (_bottom - _top);
        float m43 = (_near) / (_near - _far);

        return float4x4(
            m11, 0.0f, 0.0f, 0.0f,
            0.0f, m22, 0.0f, 0.0f,
            0.0f, 0.0f, m33, 0.0f,
            m41, m42, m43, 1.0f
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