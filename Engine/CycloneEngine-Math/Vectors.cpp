#include "Vectors.h"

namespace CycloneEngine
{
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

	Vector4::Vector4()
	{
		x = 0;
		y = 0;
	}

	Vector4::Vector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector4::~Vector4() = default;
}