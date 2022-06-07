#include "Matrix3X3.h"

#include "Mathf.h"
#include "MatrixMath.h"
#include "Matrix2X2.h"

namespace CycloneEngine
{
	Matrix3X3 Matrix3X3::Transpose(const Matrix3X3& _matrix)
	{
		Matrix3X3 result;
		MatrixMath::Transpose(_matrix.asArray, result.asArray, MATRIX_3_SIZE, MATRIX_3_SIZE);
		return result;
	}

	Matrix3X3 Matrix3X3::Inverse(const Matrix3X3& _matrix)
	{
		float det = MatrixMath::Determinant(_matrix);
		if (CMP(det, 0.0f))
			return Matrix3X3();

		return MatrixMath::Adjugate(_matrix) * (1.0f / det);
	}

	Matrix3X3 Matrix3X3::Rotation(float _pitch, float _yaw, float _roll)
	{
		return MatrixMath::ZRotation3X3(_roll) *
			MatrixMath::XRotation3X3(_pitch) *
			MatrixMath::YRotation3X3(_yaw);
	}

	Matrix3X3 Matrix3X3::AxisAngle(const Vector3& _axis, float _angle)
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
			float inv_len = 1.0f / _axis.Magnitude();
			x *= inv_len;
			y *= inv_len;
			z *= inv_len;
		}

		return Matrix3X3(
			t * (x * x) + c, t * x * y + s * z, t * x * z - s * y,
			t * x * y - s * z, t * (y * y) + c, t * y * z + s * x,
			t * x * z + s * y, t * y * z - s * x, t * (z * z) + c
		);
	}

	Matrix3X3 operator*(const Matrix3X3& _matrix, float _scalar)
	{
		Matrix3X3 result;
		for (int i = 0; i < MATRIX_3_SIZE; ++i)
		{
			result.asArray[i] = _matrix.asArray[i] * _scalar;
		}
		return result;
	}

	Matrix3X3 operator*(const Matrix3X3& _matrix, const Matrix3X3& _other)
	{
		Matrix3X3 result;
		MatrixMath::Multiply(result.asArray, _matrix.asArray, MATRIX_3_SIZE, MATRIX_3_SIZE, _other.asArray, MATRIX_3_SIZE, MATRIX_3_SIZE);
		return result;
	}
}