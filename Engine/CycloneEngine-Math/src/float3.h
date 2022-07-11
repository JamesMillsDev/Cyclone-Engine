#ifndef CYCLONE_MATH_FLOAT3
#define CYCLONE_MATH_FLOAT3

#include "CycloneMath.h"

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


		CYCLONE_DLL float3();
		CYCLONE_DLL float3(float _val);
		CYCLONE_DLL float3(float _x, float _y, float _z);

		CYCLONE_DLL float Magnitude() const;
		CYCLONE_DLL float MagnitudeSq() const;

		CYCLONE_DLL void Normalize();

		CYCLONE_DLL static float Dot(const float3& _lhs, const float3& _rhs);
		CYCLONE_DLL static float Distance(const float3& _lhs, const float3& _rhs);
		CYCLONE_DLL static float3 Normalized(const float3& _lhs);
		CYCLONE_DLL static float3 Cross(const float3& _lhs, const float3& _rhs);
		CYCLONE_DLL static float Angle(const float3& _lhs, const float3& _rhs);
		CYCLONE_DLL static float3 Project(const float3& _length, const float3& _direction);
		CYCLONE_DLL static float3 Perpendicular(const float3& _length, const float3& _direction);
		CYCLONE_DLL static float3 Reflect(const float3& _vector, const float3& _normal);
		

	} float3;

	CYCLONE_DLL float3 operator+(const float3& _lhs, const float3& _rhs);
	CYCLONE_DLL float3 operator-(const float3& _lhs, const float3& _rhs);
	CYCLONE_DLL float3 operator-(const float3& _lhs);
	CYCLONE_DLL float3 operator*(const float3& _lhs, const float3& _rhs);
	CYCLONE_DLL float3 operator*(const float3& _lhs, float _rhs);
	CYCLONE_DLL float3 operator/(const float3& _lhs, float _rhs);
	CYCLONE_DLL bool operator==(const float3& _lhs, const float3& _rhs);
	CYCLONE_DLL bool operator!=(const float3& _lhs, const float3& _rhs);
}

#endif //!CYCLONE_MATH_FLOAT3