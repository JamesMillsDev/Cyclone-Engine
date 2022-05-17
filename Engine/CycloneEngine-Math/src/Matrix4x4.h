#ifndef CYCLONE_MATH_MATRIX
#define CYCLONE_MATH_MATRIX

#include "CycloneMath.h"

#include <glm/mat4x4.hpp>
#include "Vector3.h"
#include "Quaternion.h"

using glm::mat4x4;

namespace CycloneEngine
{
	// ReSharper disable once CppInconsistentNaming
	#define MATRIX_4X4_SCALE 4

	// ReSharper disable once CppInconsistentNaming
	struct Matrix4x4
	{
		CYCLONE_DLL Matrix4x4();

		CYCLONE_DLL void scale(Vector3 _scale);
		CYCLONE_DLL void rotate(Vector3 _rotate);
		CYCLONE_DLL void rotate(Quaternion _rotate);
		CYCLONE_DLL void translate(Vector3 _translation);

		CYCLONE_DLL void setTranslation(Vector3 _translation);
		CYCLONE_DLL Vector3 getTranslation() const;
		CYCLONE_DLL void setRotation(Quaternion _rotation);
		CYCLONE_DLL Quaternion getRotation() const;
		CYCLONE_DLL void setScale(Vector3 _scale);
		CYCLONE_DLL Vector3 getScale() const;
		CYCLONE_DLL void setEuler(Vector3 _euler);
		CYCLONE_DLL Vector3 getEuler() const;

	private:
		// scale / yRot / zRot	- zRot					- yRot			- xPos
		// zRot					- scale / zRot / xRot	- xRot			- yPos
		// yRot					- xRot					- xRot / scale	- zPos
		// UNUSED				- UNUSED				- UNUSED		- UNUSED
		mat4x4 matrix;

	};
}

#endif // CYCLONE_MATH_MATRIX