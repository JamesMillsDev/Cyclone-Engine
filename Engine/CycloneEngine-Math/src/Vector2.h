#ifndef CYCLONE_MATH_VECTOR2
#define CYCLONE_MATH_VECTOR2

#include "CycloneMath.h"

namespace CycloneEngine
{
#define VECTOR_2_SIZE 2

	typedef struct Vector2
	{
		union
		{
			struct
			{
				float x;
				float y;
			};

			float asArray[VECTOR_2_SIZE];
		};

		float& operator[](const int _i)
		{
			return asArray[_i];
		}

		CYCLONE_DLL Vector2();
		CYCLONE_DLL Vector2(float _x, float _y);

		CYCLONE_DLL float Magnitude();
		CYCLONE_DLL float MagnitudeSq();

		CYCLONE_DLL void Normalize();

		CYCLONE_DLL static float Dot(const Vector2& _lhs, const Vector2& _rhs);
		CYCLONE_DLL static float Distance(const Vector2& _lhs, const Vector2& _rhs);
		CYCLONE_DLL static Vector2 Normalized(const Vector2& _lhs);
		CYCLONE_DLL static Vector2 Project(const Vector2& _length, const Vector2& _direction);
		CYCLONE_DLL static Vector2 Perpendicular(const Vector2& _length, const Vector2& _direction);
		CYCLONE_DLL static Vector2 Reflect(const Vector2& _vector, const Vector2& _normal);
	} Vector2;

	CYCLONE_DLL Vector2 operator+(const Vector2& _lhs, const Vector2& _rhs);
	CYCLONE_DLL Vector2 operator-(const Vector2& _lhs, const Vector2& _rhs);
	CYCLONE_DLL Vector2 operator*(const Vector2& _lhs, const Vector2& _rhs);
	CYCLONE_DLL Vector2 operator*(const Vector2& _lhs, const float _rhs);
	CYCLONE_DLL bool operator==(const Vector2& _lhs, const Vector2& _rhs);
	CYCLONE_DLL bool operator!=(const Vector2& _lhs, const Vector2& _rhs);
}

#endif //!CYCLONE_MATH_VECTOR2