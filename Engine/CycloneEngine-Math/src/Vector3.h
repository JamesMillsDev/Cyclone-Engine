#ifndef CYCLONE_MATH_VECTOR3
#define CYCLONE_MATH_VECTOR3

#include "CycloneMath.h"

namespace CycloneEngine
{
	#define VECTOR_3_SIZE 3

	typedef struct Vector3
	{
		union
		{
			struct
			{
				float x;
				float y;
				float z;
			};

			float asArray[VECTOR_3_SIZE];
		};

		float& operator[](int _i)
		{
			return asArray[_i];
		}

		CYCLONE_DLL Vector3();
		CYCLONE_DLL Vector3(float _x, float _y, float _z);

		CYCLONE_DLL float Magnitude() const;
		CYCLONE_DLL float MagnitudeSq() const;

		CYCLONE_DLL void Normalize();

		CYCLONE_DLL static float Dot(const Vector3& _lhs, const Vector3& _rhs);
		CYCLONE_DLL static float Distance(const Vector3& _lhs, const Vector3& _rhs);
		CYCLONE_DLL static Vector3 Normalized(const Vector3& _lhs);
		CYCLONE_DLL static Vector3 Cross(const Vector3& _lhs, const Vector3& _rhs);
		CYCLONE_DLL static float Angle(const Vector3& _lhs, const Vector3& _rhs);
		CYCLONE_DLL static Vector3 Project(const Vector3& _length, const Vector3& _direction);
		CYCLONE_DLL static Vector3 Perpendicular(const Vector3& _length, const Vector3& _direction);
		CYCLONE_DLL static Vector3 Reflect(const Vector3& _vector, const Vector3& _normal);

	} Vector3;

	CYCLONE_DLL Vector3 operator+(const Vector3& _lhs, const Vector3& _rhs);
	CYCLONE_DLL Vector3 operator-(const Vector3& _lhs, const Vector3& _rhs);
	CYCLONE_DLL Vector3 operator*(const Vector3& _lhs, const Vector3& _rhs);
	CYCLONE_DLL Vector3 operator*(const Vector3& _lhs, const float _rhs);
	CYCLONE_DLL bool operator==(const Vector3& _lhs, const Vector3& _rhs);
	CYCLONE_DLL bool operator!=(const Vector3& _lhs, const Vector3& _rhs);
}

#endif //!CYCLONE_MATH_VECTOR3