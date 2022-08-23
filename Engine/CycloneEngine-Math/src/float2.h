#ifndef CYCLONE_MATH_FLOAT2
#define CYCLONE_MATH_FLOAT2

#include <glm/vec2.hpp>

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

		float2();
		float2(float _x, float _y);
		float2(const glm::vec2& _vector);
		operator glm::vec2 const() const;

		float Magnitude() const;
		float MagnitudeSq() const;

		void Normalize();

		static float Dot(const float2& _lhs, const float2& _rhs);
		static float Distance(const float2& _lhs, const float2& _rhs);
		static float2 Normalized(const float2& _lhs);
		static float2 Project(const float2& _length, const float2& _direction);
		static float2 Perpendicular(const float2& _length, const float2& _direction);
		static float2 Reflect(const float2& _vector, const float2& _normal);
	} float2;

	float2 operator+(const float2& _lhs, const float2& _rhs);
	float2 operator-(const float2& _lhs, const float2& _rhs);
	float2 operator*(const float2& _lhs, const float2& _rhs);
	float2 operator*(const float2& _lhs, const float _rhs);
	bool operator==(const float2& _lhs, const float2& _rhs);
	bool operator!=(const float2& _lhs, const float2& _rhs);
}

#endif //!CYCLONE_MATH_VECTOR2