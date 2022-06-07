#ifndef CYCLONE_MATH_FLOAT2
#define CYCLONE_MATH_FLOAT2

#include "CycloneMath.h"

namespace CycloneEngine
{
#define FLOAT_2_SIZE 2

	typedef struct float2
	{
		union
		{
			struct
			{
				float x;
				float y;
			};

			float asArray[FLOAT_2_SIZE];
		};

		float& operator[](const int _i)
		{
			return asArray[_i];
		}

		CYCLONE_DLL float2();
		CYCLONE_DLL float2(float _x, float _y);

		CYCLONE_DLL float Magnitude();
		CYCLONE_DLL float MagnitudeSq();

		CYCLONE_DLL void Normalize();

		CYCLONE_DLL static float Dot(const float2& _lhs, const float2& _rhs);
		CYCLONE_DLL static float Distance(const float2& _lhs, const float2& _rhs);
		CYCLONE_DLL static float2 Normalized(const float2& _lhs);
		CYCLONE_DLL static float2 Project(const float2& _length, const float2& _direction);
		CYCLONE_DLL static float2 Perpendicular(const float2& _length, const float2& _direction);
		CYCLONE_DLL static float2 Reflect(const float2& _vector, const float2& _normal);
	} float2;

	CYCLONE_DLL float2 operator+(const float2& _lhs, const float2& _rhs);
	CYCLONE_DLL float2 operator-(const float2& _lhs, const float2& _rhs);
	CYCLONE_DLL float2 operator*(const float2& _lhs, const float2& _rhs);
	CYCLONE_DLL float2 operator*(const float2& _lhs, const float _rhs);
	CYCLONE_DLL bool operator==(const float2& _lhs, const float2& _rhs);
	CYCLONE_DLL bool operator!=(const float2& _lhs, const float2& _rhs);
}

#endif //!CYCLONE_MATH_VECTOR2