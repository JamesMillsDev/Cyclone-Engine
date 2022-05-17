#ifndef CYCLONE_MATH_QUATERNION
#define CYCLONE_MATH_QUATERNION

#include "CycloneMath.h"

#include <glm/gtx/quaternion.hpp>

using glm::quat;

namespace CycloneEngine
{
	struct Vector3;

	struct Quaternion
	{
		CYCLONE_DLL static float angle(Quaternion _lhs, Quaternion _rhs);
		CYCLONE_DLL static Quaternion angleAxis(Vector3 _axis, float _angle);
		//CYCLONE_DLL static float dot(Quaternion _lhs, Quaternion _rhs);
		CYCLONE_DLL static Quaternion eulerAngles(Vector3 _euler);
		//CYCLONE_DLL static Quaternion inverse(Quaternion _toInverse);

		CYCLONE_DLL Quaternion(quat _quaternion);

		CYCLONE_DLL float x() const { return intQuat.x; }
		CYCLONE_DLL float y() const { return intQuat.y; }
		CYCLONE_DLL float z() const { return intQuat.z; }
		CYCLONE_DLL float w() const { return intQuat.w; }
		CYCLONE_DLL Vector3 eulerAngles();

		explicit operator quat() const { return intQuat; }

	private:
		quat intQuat;
	};
}

#endif // !CYCLONE_MATH_QUATERNION