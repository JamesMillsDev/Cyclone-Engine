#ifndef CYCLONE_MATH_MATRIX
#define CYCLONE_MATH_MATRIX

#include <glm/mat4x4.hpp>

using glm::mat4x4;

namespace CycloneEngine
{
	struct Vector3;
	struct Quaternion;
	// ReSharper disable once CppInconsistentNaming
	#define MATRIX_4X4_SCALE 4

	// ReSharper disable once CppInconsistentNaming
	struct Matrix4x4
	{
		Matrix4x4();

		void scale(Vector3 _scale);
		void rotate(Vector3 _rotate);
		void rotate(Quaternion _rotate);
		void translate(Vector3 _translation);

	private:
		// scale / yRot / zRot	- zRot					- yRot			- xPos
		// zRot					- scale / zRot / xRot	- xRot			- yPos
		// yRot					- xRot					- xRot / scale	- zPos
		// UNUSED				- UNUSED				- UNUSED		- UNUSED
		mat4x4 matrix;

	};
}

#endif // CYCLONE_MATH_MATRIX