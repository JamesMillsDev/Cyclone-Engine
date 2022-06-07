#include "float2.h"

#include "Mathf.h"

namespace CycloneEngine
{
	float2::float2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float2::float2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float float2::Magnitude()
	{
		return sqrt(Dot(*this, *this));
	}

	float float2::MagnitudeSq()
	{
		return Dot(*this, *this);
	}

	void float2::Normalize()
	{
		float2 normalized = Normalized(*this);
		x = normalized.x;
		y = normalized.y;
	}

	float float2::Dot(const float2& _lhs, const float2& _rhs)
	{
		return _lhs.x * _rhs.x + _lhs.y * _rhs.y;
	}

	float float2::Distance(const float2& _lhs, const float2& _rhs)
	{
		return (_lhs - _rhs).Magnitude();
	}

	float2 float2::Normalized(const float2& _lhs)
	{
		float2 other = _lhs;
		return other * (1.0f / other.Magnitude());
	}

	float2 float2::Project(const float2& _length, const float2& _direction)
	{
		float2 magVec = _direction;

		const float dot = Dot(_length, _direction);
		const float magSq = magVec.MagnitudeSq();
		return _direction * (dot / magSq);
	}

	float2 float2::Perpendicular(const float2& _length, const float2& _direction)
	{
		return _length - Project(_length, _direction);
	}

	float2 float2::Reflect(const float2& _vector, const float2& _normal)
	{
		const float d = Dot(_vector, _normal);
		return _vector - _normal * (d * 2.0f );
	}

	float2 operator+(const float2& _lhs, const float2& _rhs)
	{
		return float2{ _lhs.x + _rhs.x, _lhs.y + _rhs.y };
	}

	float2 operator-(const float2& _lhs, const float2& _rhs)
	{
		return float2{ _lhs.x - _rhs.x, _lhs.y - _rhs.y };
	}

	float2 operator*(const float2& _lhs, const float2& _rhs)
	{
		return float2{ _lhs.x * _rhs.x, _lhs.y * _rhs.y };
	}

	float2 operator*(const float2& _lhs, const float _rhs)
	{
		return float2{ _lhs.x * _rhs, _lhs.y * _rhs };
	}

	bool operator==(const float2& _lhs, const float2& _rhs)
	{
		return CMP(_lhs.x, _rhs.x) && CMP(_lhs.y, _rhs.y);
	}

	bool operator!=(const float2& _lhs, const float2& _rhs)
	{
		return !CMP(_lhs.x, _rhs.x) || !CMP(_lhs.y, _rhs.y);
	}
}