#ifndef CYCLONE_MATH_MATRIX_MATH
#define CYCLONE_MATH_MATRIX_MATH

#include "CycloneMath.h"

#include "Matrix2X2.h"
#include "Matrix3X3.h"
#include "Matrix4X4.h"

namespace CycloneEngine
{
	class MatrixMath
	{
	public:
		CYCLONE_DLL static bool Multiply(float* _out, const float* _matA, int _aRows, int _aCols, const float* _matB, int _bRows, int _bCols);
		CYCLONE_DLL static void Transpose(const float* _srcMat, float* _dstMat, int _srcRows, int _srcCols);
		CYCLONE_DLL static void Cofactor(float* _out, const float* _minor, int _rows, int _cols);

		CYCLONE_DLL static float Determinant(const Matrix2X2& _matrix);
		CYCLONE_DLL static Matrix2X2 Cut(const Matrix3X3& _matrix, int _row, int _col);
		CYCLONE_DLL static Matrix2X2 Minor(const Matrix2X2& _matrix);
		CYCLONE_DLL static Matrix2X2 Cofactor(const Matrix2X2& _matrix);
		CYCLONE_DLL static Matrix2X2 Adjugate(const Matrix2X2& _matrix);

		CYCLONE_DLL static float Determinant(const Matrix3X3& _matrix);
		CYCLONE_DLL static Matrix3X3 Minor(const Matrix3X3& _matrix);
		CYCLONE_DLL static Matrix3X3 Cofactor(const Matrix3X3& _matrix);
		CYCLONE_DLL static Matrix3X3 Adjugate(const Matrix3X3& _matrix);

		CYCLONE_DLL static float Determinant(const Matrix4X4& _matrix);
		CYCLONE_DLL static Matrix3X3 Cut(const Matrix4X4& _matrix, int _row, int _col);
		CYCLONE_DLL static Matrix4X4 Minor(const Matrix4X4& _matrix);
		CYCLONE_DLL static Matrix4X4 Cofactor(const Matrix4X4& _matrix);
		CYCLONE_DLL static Matrix4X4 Adjugate(const Matrix4X4& _matrix);

		CYCLONE_DLL static Matrix4X4 XRotation(float _angle);
		CYCLONE_DLL static Matrix4X4 YRotation(float _angle);
		CYCLONE_DLL static Matrix4X4 ZRotation(float _angle);
		CYCLONE_DLL static Matrix3X3 XRotation3X3(float _angle);
		CYCLONE_DLL static Matrix3X3 YRotation3X3(float _angle);
		CYCLONE_DLL static Matrix3X3 ZRotation3X3(float _angle);
	};
}

#endif