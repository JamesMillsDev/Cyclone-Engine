#include "Matrix4x4.h"

#include "Vector3.h"

namespace CycloneEngine
{
	Matrix4x4::Matrix4x4()
		: matrix()
	{
		matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0;
		matrix[1][0] = 1; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = 0;
		matrix[2][0] = 1; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = 0;
		matrix[3][0] = 1; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
	}

	void Matrix4x4::scale(Vector3 _scale)
	{
		matrix[0][0] += _scale.x;
		matrix[1][1] += _scale.y;
		matrix[2][2] += _scale.z;
	}

	void Matrix4x4::set_scale(Vector3 _scale)
	{
		matrix[0][0] = _scale.x;
		matrix[1][1] = _scale.y;
		matrix[2][2] = _scale.z;
	}

	void Matrix4x4::translate(Vector3 _translation)
	{
		matrix[3][0] += _translation.x;
		matrix[3][1] += _translation.y;
		matrix[3][2] += _translation.z;
	}

	void Matrix4x4::set_translation(Vector3 _translation)
	{
		matrix[3][0] = _translation.x;
		matrix[3][1] = _translation.y;
		matrix[3][2] = _translation.z;
	}
}