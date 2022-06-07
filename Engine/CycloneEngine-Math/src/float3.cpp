#include "float3.h"

#include "Mathf.h"

namespace CycloneEngine
{
	float3::float3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	float3::float3(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float float3::Magnitude() const
	{
		return sqrt(Dot(*this, *this));
	}

	float float3::MagnitudeSq() const
	{
		return Dot(*this, *this);
	}

	void float3::Normalize()
	{
		const float3 normalized = Normalized(*this);
		x = normalized.x;
		y = normalized.y;
	}

	float float3::Dot(const float3& _lhs, const float3& _rhs)
	{
		return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;
	}

	float float3::Distance(const float3& _lhs, const float3& _rhs)
	{
		return (_lhs - _rhs).Magnitude();
	}

	float3 float3::Normalized(const float3& _lhs)
	{
		const float3 other = _lhs;
		return other * (1.0f / other.Magnitude());
	}

	float3 float3::Cross(const float3& _lhs, const float3& _rhs)
	{
		float3 result;

		result.x = _lhs.y * _rhs.z - _lhs.z * _rhs.y;
		result.y = _lhs.z * _rhs.x - _lhs.x * _rhs.z;
		result.z = _lhs.x * _rhs.y - _lhs.y * _rhs.x;

		return result;
	}

	float float3::Angle(const float3& _lhs, const float3& _rhs)
	{
		const float3 left = _lhs;
		const float3 right = _rhs;

		const float m = sqrtf(left.MagnitudeSq() * right.MagnitudeSq());
		return acosf(Dot(_lhs, _rhs) / m);
	}

	float3 float3::Project(const float3& _length, const float3& _direction)
	{
		const float3 magVec = _direction;

		const float dot = Dot(_length, _direction);
		const float magSq = magVec.MagnitudeSq();
		return _direction * (dot / magSq);
	}

	float3 float3::Perpendicular(const float3& _length, const float3& _direction)
	{
		return _length - Project(_length, _direction);
	}

	float3 float3::Reflect(const float3& _vector, const float3& _normal)
	{
		const float d = Dot(_vector, _normal);
		return _vector - _normal * (d * 2.0f );
	}

	float3 operator+(const float3& _lhs, const float3& _rhs)
	{
		return float3{ _lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z };
	}

	float3 operator-(const float3& _lhs, const float3& _rhs)
	{
		return float3{ _lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z + _rhs.z };
	}

	float3 operator*(const float3& _lhs, const float3& _rhs)
	{
		return float3{ _lhs.x * _rhs.x, _lhs.y * _rhs.y, _lhs.z + _rhs.z };
	}

	float3 operator*(const float3& _lhs, const float _rhs)
	{
		return float3{ _lhs.x * _rhs, _lhs.y * _rhs, _lhs.z + _rhs };
	}

	bool operator==(const float3& _lhs, const float3& _rhs)
	{
		return CMP(_lhs.x, _rhs.x) && CMP(_lhs.y, _rhs.y) && CMP(_lhs.z, _rhs.z);
	}

	bool operator!=(const float3& _lhs, const float3& _rhs)
	{
		return !CMP(_lhs.x, _rhs.x) || !CMP(_lhs.y, _rhs.y) || !CMP(_lhs.z, _rhs.z);
	}
}