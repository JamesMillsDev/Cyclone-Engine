#include "MatrixMath.h"

#include "Mathf.h"

#include <cmath>
#include <cfloat>

namespace CycloneEngine
{
	void MatrixMath::Transpose(const float* _srcMat, float* _dstMat, const int _srcRows, const int _srcCols)
	{
		for (int i = 0; i < _srcRows * _srcCols; i++)
		{
			const int row = i / _srcRows;
			const int col = i % _srcRows;
			_dstMat[i] = _srcMat[_srcCols * col + row];
		}
	}

	bool MatrixMath::Multiply(float* _out, const float* _matA, int _aRows, int _aCols, const float* _matB, int _bRows, int _bCols)
	{
		if (_aRows != _bRows)
		{
			return false;
		}

		for (int i = 0; i < _aRows; ++i)
		{
			for (int j = 0; j < _bCols; ++j)
			{
				_out[_bCols * i + j] = 0.0f;
				for (int k = 0; k < _bRows; ++k)
				{
					int a = _aCols * i + k;
					int b = _bCols * k + j;
					_out[_bCols * i + j] += _matA[a] * _matB[b];
				}
			}
		}
		return true;
	}

	void MatrixMath::Cofactor(float* _out, const float* _minor, int _rows, int _cols)
	{
		for (int i = 0; i < _rows; ++i)
		{
			for (int j = 0; j < _cols; ++j)
			{
				int t = _cols * j + i; // Target index
				int s = _cols * j + i; // Source index
				float sign = powf(-1.0f, (float)i + (float)j); // + or –
				_out[t] = _minor[s] * sign;
			}
		}
	}

	float MatrixMath::Determinant(const Matrix2X2& _matrix)
	{
		return _matrix.m11 * _matrix.m22 - _matrix.m12 * _matrix.m21;
	}

	Matrix2X2 MatrixMath::Cut(const Matrix3X3& _matrix, int _row, int _col)
	{
		Matrix2X2 result;
		int index = 0;

		for (int i = 0; i < MATRIX_3_SIZE; ++i)
		{
			for (int j = 0; j < MATRIX_3_SIZE; ++j)
			{
				if (i == _row || j == _col)
					continue;

				int target = index++;
				int source = 3 * i + j;
				result.asArray[target] = _matrix.asArray[source];
			}
		}

		return result;
	}

	Matrix2X2 MatrixMath::Minor(const Matrix2X2& _matrix)
	{
		return Matrix2X2(
			_matrix.m22, _matrix.m21,
			_matrix.m12, _matrix.m11
		);
	}

	Matrix2X2 MatrixMath::Cofactor(const Matrix2X2& _matrix)
	{
		Matrix2X2 result;
		Cofactor(result.asArray, Minor(_matrix).asArray, MATRIX_2_SIZE, MATRIX_2_SIZE);
		return result;
	}

	Matrix2X2 MatrixMath::Adjugate(const Matrix2X2& _matrix)
	{
		return Matrix2X2::Transpose(Cofactor(_matrix));
	}


	float MatrixMath::Determinant(const Matrix3X3& _matrix)
	{
		float result = 0.0f;
		Matrix3X3 cofactor = Cofactor(_matrix);
		for (int i = 0; i < MATRIX_3_SIZE; i++)
		{
			int index = MATRIX_3_SIZE * 0 + i;
			result += _matrix.asArray[index] * cofactor[0][i];
		}

		return result;
	}

	Matrix3X3 MatrixMath::Minor(const Matrix3X3& _matrix)
	{
		Matrix3X3 result;

		for (int i = 0; i < MATRIX_3_SIZE; ++i)
		{
			for (int j = 0; j < MATRIX_3_SIZE; ++j)
			{
				result[i][j] = Determinant(Cut(_matrix, i, j));
			}
		}

		return result;
	}

	Matrix3X3 MatrixMath::Cofactor(const Matrix3X3& _matrix)
	{
		Matrix3X3 result;
		Cofactor(result.asArray, Minor(_matrix).asArray, MATRIX_3_SIZE, MATRIX_3_SIZE);
		return result;
	}

	Matrix3X3 MatrixMath::Adjugate(const Matrix3X3& _matrix)
	{
		return Matrix3X3::Transpose(Cofactor(_matrix));
	}

	float MatrixMath::Determinant(const Matrix4X4& _matrix)
	{
		float result = 0.0f;

		Matrix4X4 cofactor = Cofactor(_matrix);
		for (int j = 0; j < MATRIX_4_SIZE; ++j)
		{
			result += _matrix.asArray[MATRIX_4_SIZE * 0 + j] * cofactor[0][j];
		}

		return result;
	}

	Matrix3X3 MatrixMath::Cut(const Matrix4X4& _matrix, int _row, int _col)
	{
		Matrix3X3 result;
		int index = 0;

		for (int i = 0; i < MATRIX_4_SIZE; ++i)
		{
			for (int j = 0; j < MATRIX_4_SIZE; ++j)
			{
				if (i == _row || j == _col)
					continue;

				int target = index++;
				int source = 4 * i + j;
				result.asArray[target] = _matrix.asArray[source];
			}
		}

		return result;
	}

	Matrix4X4 MatrixMath::Minor(const Matrix4X4& _matrix)
	{
		Matrix4X4 result;

		for (int i = 0; i < MATRIX_4_SIZE; ++i)
		{
			for (int j = 0; j < MATRIX_4_SIZE; ++j)
			{
				result[i][j] = Determinant(Cut(_matrix, i, j));
			}
		}

		return result;
	}

	Matrix4X4 MatrixMath::Cofactor(const Matrix4X4& _matrix)
	{
		Matrix4X4 result;
		Cofactor(result.asArray, Minor(_matrix).asArray, 4, 4);
		return result;
	}

	Matrix4X4 MatrixMath::Adjugate(const Matrix4X4& _matrix)
	{
		return Matrix4X4::Transpose(Cofactor(_matrix));
	}

	Matrix4X4 MatrixMath::XRotation(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return Matrix4X4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosf(_angle), sinf(_angle), 0.0f,
			0.0f, -sinf(_angle), cos(_angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4X4 MatrixMath::YRotation(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return Matrix4X4(
			cosf(_angle), 0.0f, -sinf(_angle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinf(_angle), 0.0f, cosf(_angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix4X4 MatrixMath::ZRotation(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return Matrix4X4(
			cosf(_angle), sinf(_angle), 0.0f, 0.0f,
			-sinf(_angle), cosf(_angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	Matrix3X3 MatrixMath::XRotation3X3(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return Matrix3X3(
			1.0f, 0.0f, 0.0f,
			0.0f, cosf(_angle), sinf(_angle),
			0.0f, -sinf(_angle), cos(_angle)
		);
	}

	Matrix3X3 MatrixMath::YRotation3X3(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return Matrix3X3(
			cosf(_angle), 0.0f, -sinf(_angle),
			0.0f, 1.0f, 0.0f,
			sinf(_angle), 0.0f, cosf(_angle)
		);
	}

	Matrix3X3 MatrixMath::ZRotation3X3(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return Matrix3X3(
			cosf(_angle), sinf(_angle), 0.0f,
			-sinf(_angle), cosf(_angle), 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}
}