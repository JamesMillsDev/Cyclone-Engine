#ifndef CYCLONE_MATH_VECTOR3
#define CYCLONE_MATH_VECTOR3

#include <glm/vec3.hpp>

using glm::vec3;

namespace CycloneEngine
{
	struct Vector3
	{
	public:
		static Vector3 zero;
		static Vector3 one;
		static Vector3 up;
		static Vector3 down;
		static Vector3 right;
		static Vector3 left;
		static Vector3 forward;
		static Vector3 back;

		Vector3();
		Vector3(float _x, float _y, float _z);
		Vector3(vec3 _vector);
		~Vector3();

		float x;
		float y;
		float z;

		float magnitude();
		void normalize();
		static float dot(Vector3 _lhs, Vector3 _rhs);
		static Vector3 cross(Vector3 _lhs, Vector3 _rhs);
		static float angle(Vector3 _lhs, Vector3 _rhs);
		static float distance(Vector3 _lhs, Vector3 _rhs);

		Vector3 operator*(float _rhs) const { return Vector3{ x * _rhs, y * _rhs, z * _rhs }; }
		Vector3 operator*=(float _rhs) const { return Vector3{ x * _rhs, y * _rhs, z * _rhs }; }
		Vector3 operator/(float _rhs) const { return Vector3{ x / _rhs, y / _rhs, z / _rhs }; }
		Vector3 operator/=(float _rhs) const { return Vector3{ x / _rhs, y / _rhs, z / _rhs }; }
		Vector3 operator+(Vector3 _rhs) const { return Vector3{ x + _rhs.x, y + _rhs.y, z + _rhs.z }; }
		Vector3 operator+=(Vector3 _rhs) const { return Vector3{ x + _rhs.x, y + _rhs.y, z + _rhs.z }; }
		Vector3 operator-(Vector3 _rhs) const { return Vector3{ x - _rhs.x, y - _rhs.y, z - _rhs.z }; }
		Vector3 operator-=(Vector3 _rhs) const { return Vector3{ x - _rhs.x, y - _rhs.y, z - _rhs.z }; }

		operator vec3() const { return vec3(x, y, z); }

	};
}

#endif //!CYCLONE_MATH_VECTOR3