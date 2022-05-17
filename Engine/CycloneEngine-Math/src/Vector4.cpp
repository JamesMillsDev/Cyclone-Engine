#include "Vector4.h"

#include <math.h>
#include "Mathf.h"

namespace CycloneEngine
{
	Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
	Vector4 Vector4::one = Vector4(1, 1, 0, 0);
	Vector4 Vector4::up = Vector4(0, 1, 0, 0);
	Vector4 Vector4::down = Vector4(0, -1, 0, 0);
	Vector4 Vector4::right = Vector4(1, 0, 0, 0);
	Vector4 Vector4::left = Vector4(-1, 0, 0, 0);
	Vector4 Vector4::forward = Vector4(0, 0, 1, 0);
	Vector4 Vector4::back = Vector4(0, 0, -1, 0);

	Vector4::Vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4::Vector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector4::~Vector4() = default;

	float Vector4::magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Vector4::normalize()
	{
		Vector4 output = Vector4{ x, y, z, w } / magnitude();
		x = output.x;
		y = output.y;
		z = output.z;
		w = output.w;
	}

	float Vector4::dot(Vector4 _lhs, Vector4 _rhs)
	{
		return (_lhs.x * _rhs.x) + (_lhs.y * _rhs.y) + (_lhs.z * _rhs.z) + (_lhs.w * _rhs.w);
	}

	float Vector4::angle(Vector4 _lhs, Vector4 _rhs)
	{
		float denominator = (float)sqrt(_lhs.magnitude() * _rhs.magnitude());
		if (denominator < FLT_EPSILON)
			return 0;

		float dotProd = Mathf::clamp(dot(_lhs, _rhs) / denominator, -1, 1);
		return acos(dotProd) * Mathf::radToDeg;
	}

	float Vector4::distance(Vector4 _lhs, Vector4 _rhs)
	{
		float xDiff = _lhs.x - _rhs.x;
		float yDiff = _lhs.y - _rhs.y;
		float zDiff = _lhs.z - _rhs.z;
		float wDiff = _lhs.w - _rhs.w;

		return sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff + wDiff * wDiff);
	}
}