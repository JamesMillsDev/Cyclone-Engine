#include "Matrix4x4.h"

#include <glm/gtx/transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/matrix_decompose.hpp>

using glm::vec4;

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

	void Matrix4x4::setTranslation(const Vector3 _translation)
	{
		matrix[3] = vec4((vec3)_translation, 1);
	}

	Vector3 Matrix4x4::getTranslation() const
	{
		return Vector3
		{ 
			matrix[3] 
		};
	}

	void Matrix4x4::setRotation(Quaternion _rotation)
	{
		vec3 scale;
		quat rotation;
		vec3 translation;
		vec3 skew;
		vec4 perspective;

		glm::decompose(matrix, scale, rotation, translation, skew, perspective);

		matrix = glm::toMat4((quat)_rotation);
		matrix *= glm::scale(scale);
		matrix *= glm::translate(translation);
	}

	Quaternion Matrix4x4::getRotation() const
	{
		return Quaternion(quat(matrix));
	}

	void Matrix4x4::setScale(Vector3 _scale)
	{
		vec3 scale;
		quat rotation;
		vec3 translation;
		vec3 skew;
		vec4 perspective;

		glm::decompose(matrix, scale, rotation, translation, skew, perspective);

		matrix = glm::scale((vec3)_scale);
		matrix *= glm::toMat4(rotation);
		matrix *= glm::translate(translation);
	}

	Vector3 Matrix4x4::getScale() const 
	{ 
		return Vector3
		{ 
			matrix[0][0], 
			matrix[1][1], 
			matrix[2][2] 
		}; 
	}

	void Matrix4x4::setEuler(Vector3 _rotation)
	{
		setRotation(Quaternion::eulerAngles(_rotation));
	}

	Vector3 Matrix4x4::getEuler() const
	{
		return Vector3(glm::eulerAngles(quat(matrix)));
	}
}