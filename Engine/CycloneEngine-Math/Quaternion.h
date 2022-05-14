#ifndef CYCLONE_MATH_QUATERNION
#define CYCLONE_MATH_QUATERNION

#include <glm/gtx/quaternion.hpp>

using glm::quat;

namespace CycloneEngine
{
	struct Vector3;

	struct Quaternion
	{
	public:
		static float angle(Quaternion _lhs, Quaternion _rhs);
		static Quaternion angle_axis(Vector3 _axis, float _angle);
		static float dot(Quaternion _lhs, Quaternion _rhs);
		static Quaternion euler_angles(Vector3 _euler);
		static Quaternion inverse(Quaternion _toInverse);

		Quaternion(quat _quaternion);

		float x() const { return intQuat.x; }
		float y() const { return intQuat.y; }
		float z() const { return intQuat.z; }
		float w() const { return intQuat.w; }
		Vector3 euler_angles();

		operator quat() const { return intQuat; }

	private:
		quat intQuat;
	};
}

#endif // !CYCLONE_MATH_QUATERNION