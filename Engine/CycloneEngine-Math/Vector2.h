#ifndef CYCLONE_MATH_VECTOR2
#define CYCLONE_MATH_VECTOR2

#include <glm/vec2.hpp>

using glm::vec2;

namespace CycloneEngine
{
	struct Vector2
	{
		static Vector2 zero;
		static Vector2 one;
		static Vector2 up;
		static Vector2 down;
		static Vector2 right;
		static Vector2 left;

		Vector2();
		Vector2(float _x, float _y);
		~Vector2();

		float x;
		float y;

		float magnitude() const;
		void normalize();
		static float dot(Vector2 _lhs, Vector2 _rhs);
		static float angle(Vector2 _lhs, Vector2 _rhs);
		static float distance(Vector2 _lhs, Vector2 _rhs);

		Vector2 operator*(const float _rhs) const { return Vector2{ x * _rhs, y * _rhs }; }
		Vector2 operator*=(const float _rhs) const { return Vector2{ x * _rhs, y * _rhs }; }
		Vector2 operator/(const float _rhs) const { return Vector2{ x / _rhs, y / _rhs }; }
		Vector2 operator/=(const float _rhs) const { return Vector2{ x / _rhs, y / _rhs }; }
		Vector2 operator+(const Vector2 _rhs) const { return Vector2{ x + _rhs.x, y + _rhs.y }; }
		Vector2 operator+=(const Vector2 _rhs) const { return Vector2{ x + _rhs.x, y + _rhs.y }; }
		Vector2 operator-(const Vector2 _rhs) const { return Vector2{ x - _rhs.x, y - _rhs.y }; }
		Vector2 operator-=(const Vector2 _rhs) const { return Vector2{ x - _rhs.x, y - _rhs.y }; }

		explicit operator vec2() const { return vec2(x, y); }

	};
}

#endif //!CYCLONE_MATH_VECTOR2