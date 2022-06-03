#include "Vector2.h"

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

	float Vector2::magnitude()
	{
		return sqrt(Dot(*this, *this));
	}

	float Vector2::magnitudeSq()
	{
		return Dot(*this, *this);
	}

	void Vector2::normalize()
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
		return (_lhs - _rhs).magnitude();
	}

	Vector2 Vector2::Normalized(const Vector2& _lhs)
	{
		Vector2 other = _lhs;
		return other * (1.0f / other.magnitude());
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