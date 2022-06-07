#include "float3x3.h"

#include "Mathf.h"
#include "MatrixMath.h"
#include "float2x2.h"

namespace CycloneEngine
{
	float3x3 float3x3::Transpose(const float3x3& _matrix)
	{
		float3x3 result;
		MatrixMath::Transpose(_matrix.asArray, result.asArray, FLOAT3X3_SIZE, FLOAT3X3_SIZE);
		return result;
	}

	float3x3 float3x3::Inverse(const float3x3& _matrix)
	{
		float det = MatrixMath::Determinant(_matrix);
		if (CMP(det, 0.0f))
			return float3x3();

		return MatrixMath::Adjugate(_matrix) * (1.0f / det);
	}

	float3x3 float3x3::Rotation(float _pitch, float _yaw, float _roll)
	{
		return MatrixMath::ZRotation3X3(_roll) *
			MatrixMath::XRotation3X3(_pitch) *
			MatrixMath::YRotation3X3(_yaw);
	}

	float3x3 float3x3::AxisAngle(const float3& _axis, float _angle)
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

		return float3x3(
			t * (x * x) + c, t * x * y + s * z, t * x * z - s * y,
			t * x * y - s * z, t * (y * y) + c, t * y * z + s * x,
			t * x * z + s * y, t * y * z - s * x, t * (z * z) + c
		);
	}

	float3x3 operator*(const float3x3& _matrix, float _scalar)
	{
		float3x3 result;
		for (int i = 0; i < FLOAT3X3_SIZE; ++i)
		{
			result.asArray[i] = _matrix.asArray[i] * _scalar;
		}
		return result;
	}

	float3x3 operator*(const float3x3& _matrix, const float3x3& _other)
	{
		float3x3 result;
		MatrixMath::Multiply(result.asArray, _matrix.asArray, FLOAT3X3_SIZE, FLOAT3X3_SIZE, _other.asArray, FLOAT3X3_SIZE, FLOAT3X3_SIZE);
		return result;
	}
}