#include "Vector2.h"

#include <math.h>
#include "Mathf.h"

namespace CycloneEngine
{
	Vector2 Vector2::zero = Vector2(0, 0);
	Vector2 Vector2::one = Vector2(1, 1);
	Vector2 Vector2::up = Vector2(0, 1);
	Vector2 Vector2::down = Vector2(0, -1);
	Vector2 Vector2::right = Vector2(1, 0);
	Vector2 Vector2::left = Vector2(-1, 0);

	Vector2::Vector2()
	{
		x = 0;
		y = 0;
	}

	Vector2::Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2::~Vector2() = default;

	float Vector2::magnitude()
	{
		return sqrt(x * x + y * y);
	}

	void Vector2::normalize()
	{
		Vector2 output = Vector2{ x, y } / magnitude();
		x = output.x;
		y = output.y;
	}

	float Vector2::dot(Vector2 _lhs, Vector2 _rhs)
	{
		return (_lhs.x * _rhs.x) + (_lhs.y * _rhs.y);
	}

	float Vector2::angle(Vector2 _lhs, Vector2 _rhs)
	{
		float denominator = (float)sqrt(_lhs.magnitude() * _rhs.magnitude());
		if (denominator < FLT_EPSILON)
			return 0;

		float dotProd = Mathf::clamp(dot(_lhs, _rhs) / denominator, -1, 1);
		return acos(dotProd) * Mathf::radToDeg;
	}

	float Vector2::distance(Vector2 _lhs, Vector2 _rhs)
	{
		float xDiff = _lhs.x - _rhs.x;
		float yDiff = _lhs.y - _rhs.y;

		return sqrt(xDiff * xDiff + yDiff * yDiff);
	}
}