#include "Vector2.h"

#include <xlocale>

#include "Mathf.h"

namespace CycloneEngine
{
	Vector2::Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2::Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float Vector2::Magnitude()
	{
		return sqrt(Dot(*this, *this));
	}

	float Vector2::MagnitudeSq()
	{
		return Dot(*this, *this);
	}

	void Vector2::Normalize()
	{
		Vector2 normalized = Normalized(*this);
		x = normalized.x;
		y = normalized.y;
	}

	float Vector2::Dot(const Vector2& _lhs, const Vector2& _rhs)
	{
		return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
	}

	float Vector2::Distance(const Vector2& _lhs, const Vector2& _rhs)
	{
		return (_lhs - _rhs).Magnitude();
	}

	Vector2 Vector2::Normalized(const Vector2& _lhs)
	{
		Vector2 other = _lhs;
		return other * (1.0f / other.Magnitude());
	}

	Vector2 Vector2::Project(const Vector2& _length, const Vector2& _direction)
	{
		Vector2 magVec = _direction;

		const float dot = Dot(_length, _direction);
		const float magSq = magVec.MagnitudeSq();
		return _direction * (dot / magSq);
	}

	Vector2 Vector2::Perpendicular(const Vector2& _length, const Vector2& _direction)
	{
		return _length - Project(_length, _direction);
	}

	Vector2 Vector2::Reflect(const Vector2& _vector, const Vector2& _normal)
	{
		const float d = Dot(_vector, _normal);
		return _vector - _normal * (d * 2.0f );
	}

	Vector2 operator+(const Vector2& _lhs, const Vector2& _rhs)
	{
		return Vector2{ _lhs.x + _rhs.x, _lhs.y + _rhs.y };
	}

	Vector2 operator-(const Vector2& _lhs, const Vector2& _rhs)
	{
		return Vector2{ _lhs.x - _rhs.x, _lhs.y - _rhs.y };
	}

	Vector2 operator*(const Vector2& _lhs, const Vector2& _rhs)
	{
		return Vector2{ _lhs.x * _rhs.x, _lhs.y * _rhs.y };
	}

	Vector2 operator*(const Vector2& _lhs, const float _rhs)
	{
		return Vector2{ _lhs.x * _rhs, _lhs.y * _rhs };
	}

	bool operator==(const Vector2& _lhs, const Vector2& _rhs)
	{
		return CMP(_lhs.x, _rhs.x) && CMP(_lhs.y, _rhs.y);
	}

	bool operator!=(const Vector2& _lhs, const Vector2& _rhs)
	{
		return !CMP(_lhs.x, _rhs.x) || !CMP(_lhs.y, _rhs.y);
	}
}