#include "Matrix4X4.h"

#include "Mathf.h"
#include "MatrixMath.h"

namespace CycloneEngine
{
    Matrix4X4 Matrix4X4::Transpose(const Matrix4X4& _matrix)
    {
        Matrix4X4 result;
        MatrixMath::Transpose(_matrix.asArray, result.asArray, MATRIX_4_SIZE, MATRIX_4_SIZE);
        return result;
    }

    Matrix4X4 Matrix4X4::Inverse(const Matrix4X4& _matrix)
    {
        float det = MatrixMath::Determinant(_matrix);
        if (CMP(det, 0.0f))
            return Matrix4X4();

        return MatrixMath::Adjugate(_matrix) * (1.0f / det);
    }

    Matrix4X4 Matrix4X4::Translation(const float _x, const float _y, const float _z)
    {
        return Matrix4X4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _x, _y, _z, 1.0f
        );
    }

    Matrix4X4 Matrix4X4::Translation(const Vector3& _pos)
    {
        return Matrix4X4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            _pos.x, _pos.y, _pos.z, 1.0f
        );
    }

    Vector3 Matrix4X4::GetTranslation(const Matrix4X4& _matrix)
    {
        return Vector3(_matrix.m41, _matrix.m42, _matrix.m43);
    }

    Matrix4X4 Matrix4X4::Scale(const float _x, const float _y, const float _z)
    {
        return Matrix4X4(
            _x, 0.0f, 0.0f, 0.0f,
            0.0f, _y, 0.0f, 0.0f,
            0.0f, 0.0f, _z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix4X4 Matrix4X4::Scale(const Vector3& _scale)
    {
        return Matrix4X4(
            _scale.x, 0.0f, 0.0f, 0.0f,
            0.0f, _scale.y, 0.0f, 0.0f,
            0.0f, 0.0f, _scale.z, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Vector3 Matrix4X4::GetScale(const Matrix4X4& _matrix)
    {
        return Vector3(_matrix.m11, _matrix.m22, _matrix.m33);
    }

    Matrix4X4 Matrix4X4::Rotation(float _pitch, float _yaw, float _roll)
    {
        return MatrixMath::ZRotation(_roll) *
            MatrixMath::XRotation(_pitch) *
            MatrixMath::YRotation(_yaw);
    }

    Matrix4X4 Matrix4X4::AxisAngle(const Vector3& _axis, float _angle)
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

        return Matrix4X4(
            t * (x * x) + c, t * x * y + s * z, t * x * z - s * y, 0.0f,
            t * x * y - s * z, t * (y * y) + c, t * y * z + s * x, 0.0f,
            t * x * z + s * y, t * y * z + s * x, t * (z * z) + c, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        );
    }

    Matrix4X4 operator*(const Matrix4X4& _matrix, float _scalar)
    {
        Matrix4X4 result;
        for (int i = 0; i < MATRIX_4_SIZE; ++i)
        {
            result.asArray[i] = _matrix.asArray[i] * _scalar;
        }
        return result;
    }

    Matrix4X4 operator*(const Matrix4X4& _matrix, const Matrix4X4& _other)
    {
        Matrix4X4 result;
        MatrixMath::Multiply(result.asArray, _matrix.asArray, MATRIX_4_SIZE, MATRIX_4_SIZE, _other.asArray, MATRIX_4_SIZE, MATRIX_4_SIZE);
        return result;
    }
}