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

	Vector3::Vector3(const float _x, const float _y, const float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	float Vector3::Magnitude() const
	{
		return sqrt(Dot(*this, *this));
	}

	float Vector3::MagnitudeSq() const
	{
		return Dot(*this, *this);
	}

	void Vector3::Normalize()
	{
		const Vector3 normalized = Normalized(*this);
		x = normalized.x;
		y = normalized.y;
	}

	float Vector3::Dot(const Vector3& _lhs, const Vector3& _rhs)
	{
		return _lhs.x * _rhs.x + _lhs.y * _rhs.y + _lhs.z * _rhs.z;
	}

	float Vector3::Distance(const Vector3& _lhs, const Vector3& _rhs)
	{
		return (_lhs - _rhs).Magnitude();
	}

	Vector3 Vector3::Normalized(const Vector3& _lhs)
	{
		const Vector3 other = _lhs;
		return other * (1.0f / other.Magnitude());
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
		const Vector3 left = _lhs;
		const Vector3 right = _rhs;

		const float m = sqrtf(left.MagnitudeSq() * right.MagnitudeSq());
		return acosf(Dot(_lhs, _rhs) / m);
	}

	Vector3 Vector3::Project(const Vector3& _length, const Vector3& _direction)
	{
		const Vector3 magVec = _direction;

		const float dot = Dot(_length, _direction);
		const float magSq = magVec.MagnitudeSq();
		return _direction * (dot / magSq);
	}

	Vector3 Vector3::Perpendicular(const Vector3& _length, const Vector3& _direction)
	{
		return _length - Project(_length, _direction);
	}

	Vector3 Vector3::Reflect(const Vector3& _vector, const Vector3& _normal)
	{
		const float d = Dot(_vector, _normal);
		return _vector - _normal * (d * 2.0f );
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