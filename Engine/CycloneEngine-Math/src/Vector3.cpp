#include "Vector3.h"

#include "Mathf.h"

namespace CycloneEngine
{
	Vector3::Vector3()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3::Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float Vector3::magnitude()
	{
		return sqrt(Dot(*this, *this));
	}

	float Vector3::magnitudeSq()
	{
		return Dot(*this, *this);
	}

	void Vector3::normalize()
	{
		Vector3 normalized = Normalized(*this);
		x = normalized.x;
		y = normalized.y;
	}

	float Vector3::Dot(const Vector3& _lhs, const Vector3& _rhs)
	{
		return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;
	}

	float Vector3::Distance(const Vector3& _lhs, const Vector3& _rhs)
	{
		return (_lhs - _rhs).magnitude();
	}

	Vector3 Vector3::Normalized(const Vector3& _lhs)
	{
		Vector3 other = _lhs;
		return other * (1.0f / other.magnitude());
	}

	Vector3 Vector3::Cross(const Vector3& _lhs, const Vector3& _rhs)
	{
		Vector3 result;

		result.x = _lhs.y * _rhs.z - _lhs.z * _rhs.y;
		result.y = _lhs.z * _rhs.x - _lhs.x * _rhs.z;
		result.z = _lhs.x * _rhs.y - _lhs.y * _rhs.x;

		return result;
	}

	float Vector3::Angle(const Vector3& _lhs, const Vector3& _rhs)
	{
		Vector3 left = _lhs;
		Vector3 right = _rhs;

		float m = sqrtf(left.magnitudeSq() * right.magnitudeSq());
		return acosf(Dot(_lhs, _rhs) / m);
	}

	Vector3 operator+(const Vector3& _lhs, const Vector3& _rhs)
	{
		return Vector3{ _lhs.x + _rhs.x, _lhs.y + _rhs.y, _lhs.z + _rhs.z };
	}

	Vector3 operator-(const Vector3& _lhs, const Vector3& _rhs)
	{
		return Vector3{ _lhs.x - _rhs.x, _lhs.y - _rhs.y, _lhs.z + _rhs.z };
	}

	Vector3 operator*(const Vector3& _lhs, const Vector3& _rhs)
	{
		return Vector3{ _lhs.x * _rhs.x, _lhs.y * _rhs.y, _lhs.z + _rhs.z };
	}

	Vector3 operator*(const Vector3& _lhs, const float _rhs)
	{
		return Vector3{ _lhs.x * _rhs, _lhs.y * _rhs, _lhs.z + _rhs };
	}

	bool operator==(const Vector3& _lhs, const Vector3& _rhs)
	{
		return CMP(_lhs.x, _rhs.x) && CMP(_lhs.y, _rhs.y) && CMP(_lhs.z, _rhs.z);
	}

	bool operator!=(const Vector3& _lhs, const Vector3& _rhs)
	{
		return !CMP(_lhs.x, _rhs.x) || !CMP(_lhs.y, _rhs.y) || !CMP(_lhs.z, _rhs.z);
	}
}