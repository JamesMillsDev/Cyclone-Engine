#include "Quaternion.h"

#include "Vector3.h"

namespace CycloneEngine
{
	Quaternion::Quaternion(quat _quaternion) : intQuat(_quaternion) {}

	float Quaternion::angle(Quaternion _lhs, Quaternion _rhs)
	{
		Vector3 left = Vector3(glm::eulerAngles((quat)_lhs));
		Vector3 right = Vector3(glm::eulerAngles((quat)_rhs));

		return Vector3::angle(left, right);
	}

	Vector3 Quaternion::eulerAngles()
	{
		return Vector3(glm::eulerAngles(intQuat));
	}

	Quaternion Quaternion::angleAxis(Vector3 _axis, float _angle)
	{
		return Quaternion(glm::angleAxis(_angle, (vec3)_axis));
	}
}