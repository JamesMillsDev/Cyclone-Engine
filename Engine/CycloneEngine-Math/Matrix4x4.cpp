#include "Matrix4x4.h"

#include "Vector3.h"
#include "Quaternion.h"

#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>

namespace CycloneEngine
{
	Matrix4x4::Matrix4x4() : matrix()
	{
		matrix = glm::identity<mat4x4>();
	}

	void Matrix4x4::scale(const Vector3 _scale)
	{
		matrix *= glm::scale((vec3)_scale);
	}

	void Matrix4x4::rotate(const Vector3 _rotate)
	{
		rotate(Quaternion::eulerAngles(_rotate));
	}

	void Matrix4x4::rotate(const Quaternion _rotate)
	{
		matrix *= toMat4((quat)_rotate);
	}

	void Matrix4x4::translate(const Vector3 _translation)
	{
		matrix *= glm::translate((vec3)_translation);
	}
}