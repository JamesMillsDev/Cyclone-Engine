#ifndef CYCLONE_MATH_MATRIX
#define CYCLONE_MATH_MATRIX

namespace CycloneEngine
{
	struct Vector3;
	#define MATRIX_4X4_SCALE 4

	struct Matrix4x4
	{
	public:
		Matrix4x4();

		void scale(Vector3 _scale);
		void set_scale(Vector3 _scale);
		void rotate(Vector3 _rotate);
		void set_rotation(Vector3 _rotate);
		void translate(Vector3 _translation);
		void set_translation(Vector3 _translation);

	private:
		// scale / yRot / zRot	- zRot					- yRot			- xPos
		// zRot					- scale / zRot / xRot	- xRot			- yPos
		// yRot					- xRot					- xRot / scale	- zPos
		// UNUSED				- UNUSED				- UNUSED		- UNUSED
		float matrix[MATRIX_4X4_SCALE][MATRIX_4X4_SCALE];

	};
}

#endif // CYCLONE_MATH_MATRIX