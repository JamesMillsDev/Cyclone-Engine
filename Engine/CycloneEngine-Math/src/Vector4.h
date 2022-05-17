#ifndef CYCLONE_MATH_VECTOR4
#define CYCLONE_MATH_VECTOR4

#include "CycloneMath.h"

#include <glm/vec4.hpp>

using glm::vec4;

namespace CycloneEngine
{
	struct Vector4
	{
		static Vector4 zero;
		static Vector4 one;
		static Vector4 up;
		static Vector4 down;
		static Vector4 right;
		static Vector4 left;
		static Vector4 forward;
		static Vector4 back;

		CYCLONE_DLL Vector4();
		CYCLONE_DLL Vector4(float _x, float _y, float _z, float _w);
		CYCLONE_DLL ~Vector4();

		float x;
		float y;
		float z;
		float w;

		CYCLONE_DLL float magnitude();
		CYCLONE_DLL void normalize();
		CYCLONE_DLL static float dot(Vector4 _lhs, Vector4 _rhs);
		CYCLONE_DLL static float angle(Vector4 _lhs, Vector4 _rhs);
		CYCLONE_DLL static float distance(Vector4 _lhs, Vector4 _rhs);

		Vector4 operator*(const float _rhs) const { return Vector4{ x * _rhs, y * _rhs, z * _rhs, w }; }
		Vector4 operator*=(const float _rhs) const { return Vector4{ x * _rhs, y * _rhs, z * _rhs, w }; }
		Vector4 operator/(const float _rhs) const { return Vector4{ x / _rhs, y / _rhs, z / _rhs, w }; }
		Vector4 operator/=(const float _rhs) const { return Vector4{ x / _rhs, y / _rhs, z / _rhs, w }; }
		Vector4 operator+(const Vector4 _rhs) const { return Vector4{ x + _rhs.x, y + _rhs.y, z + _rhs.z, w }; }
		Vector4 operator+=(const Vector4 _rhs) const { return Vector4{ x + _rhs.x, y + _rhs.y, z + _rhs.z, w }; }
		Vector4 operator-(const Vector4 _rhs) const { return Vector4{ x - _rhs.x, y - _rhs.y, z - _rhs.z, w }; }
		Vector4 operator-=(const Vector4 _rhs) const { return Vector4{ x - _rhs.x, y - _rhs.y, z - _rhs.z, w }; }

		explicit operator vec4() const { return vec4(x, y, z, w); }

	};
}

#endif // !CYCLONE_MATH_VECTOR4