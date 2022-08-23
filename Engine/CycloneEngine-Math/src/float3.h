#ifndef CYCLONE_MATH_FLOAT3
#define CYCLONE_MATH_FLOAT3

#include <glm/vec3.hpp>

namespace CycloneEngine
{
	#define FLOAT_3_SIZE 3

	typedef struct float3
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			float asArray[FLOAT_3_SIZE];
		};

		float& operator[](int _i)
		{
			return asArray[_i];
		}


		float3();
		float3(float _val);
		float3(float _x, float _y, float _z);
		float3(const glm::vec3& _vector);
		operator glm::vec3 const() const;

		float Magnitude() const;
		float MagnitudeSq() const;

		void Normalize();

		static float Dot(const float3& _lhs, const float3& _rhs);
		static float Distance(const float3& _lhs, const float3& _rhs);
		static float3 Normalized(const float3& _lhs);
		static float3 Cross(const float3& _lhs, const float3& _rhs);
		static float Angle(const float3& _lhs, const float3& _rhs);
		static float3 Project(const float3& _length, const float3& _direction);
		static float3 Perpendicular(const float3& _length, const float3& _direction);
		static float3 Reflect(const float3& _vector, const float3& _normal);
		
	} float3;

	float3 operator+(const float3& _lhs, const float3& _rhs);
	float3 operator-(const float3& _lhs, const float3& _rhs);
	float3 operator-(const float3& _lhs);
	float3 operator+=(float3& _lhs, const float3& _rhs);
	float3 operator-=(float3& _lhs, const float3& _rhs);
	float3 operator*(const float3& _lhs, const float3& _rhs);
	float3 operator*(const float3& _lhs, float _rhs);
	float3 operator/(const float3& _lhs, float _rhs);
	bool operator==(const float3& _lhs, const float3& _rhs);
	bool operator!=(const float3& _lhs, const float3& _rhs);
}

#endif //!CYCLONE_MATH_FLOAT3