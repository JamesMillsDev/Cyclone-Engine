#include "Vector3.h"

#include <math.h>
#include "Mathf.h"

namespace CycloneEngine
{
	Vector3 Vector3::zero = Vector3(0, 0, 0);
	Vector3 Vector3::one = Vector3(1, 1, 0);
	Vector3 Vector3::up = Vector3(0, 1, 0);
	Vector3 Vector3::down = Vector3(0, -1, 0);
	Vector3 Vector3::right = Vector3(1, 0, 0);
	Vector3 Vector3::left = Vector3(-1, 0, 0);
	Vector3 Vector3::forward = Vector3(0, 0, 1);
	Vector3 Vector3::back = Vector3(0, 0, -1);

	Vector3::Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3::Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3::~Vector3() = default;

	float Vector3::magnitude()
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Vector3::normalize()
	{
		Vector3 output = Vector3{ x, y, z } / magnitude();
		x = output.x;
		y = output.y;
		z = output.z;
	}

	float Vector3::dot(Vector3 _lhs, Vector3 _rhs)
	{
		return (_lhs.x * _rhs.x) + (_lhs.y * _rhs.y) + (_lhs.z * _rhs.z);
	}

	Vector3 Vector3::cross(Vector3 _lhs, Vector3 _rhs)
	{
		return Vector3
		{
			(_lhs.y * _rhs.z) - (_lhs.z * _rhs.y),
			(_lhs.z * _rhs.x) - (_lhs.x * _rhs.z),
			(_lhs.x * _rhs.y) - (_lhs.z * _rhs.y)
		};
	}

	float Vector3::angle(Vector3 _lhs, Vector3 _rhs)
	{
		float denominator = (float)sqrt(_lhs.magnitude() * _rhs.magnitude());
		if (denominator < FLT_EPSILON)
			return 0;

		float dotProd = Mathf::clamp(dot(_lhs, _rhs) / denominator, -1, 1);
		return acos(dotProd) * Mathf::radToDeg;
	}

	float Vector3::distance(Vector3 _lhs, Vector3 _rhs)
	{
		float xDiff = _lhs.x - _rhs.x;
		float yDiff = _lhs.y - _rhs.y;
		float zDiff = _lhs.z - _rhs.z;

		return sqrt(xDiff * xDiff + yDiff * yDiff + zDiff * zDiff);
	}
}