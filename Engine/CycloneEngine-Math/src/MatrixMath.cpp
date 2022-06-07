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

	float MatrixMath::Determinant(const float2x2& _matrix)
	{
		return _matrix.m11 * _matrix.m22 - _matrix.m12 * _matrix.m21;
	}

	float2x2 MatrixMath::Cut(const float3x3& _matrix, int _row, int _col)
	{
		float2x2 result;
		int index = 0;

		for (int i = 0; i < FLOAT3X3_SIZE; ++i)
		{
			for (int j = 0; j < FLOAT3X3_SIZE; ++j)
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

	float2x2 MatrixMath::Minor(const float2x2& _matrix)
	{
		return float2x2(
			_matrix.m22, _matrix.m21,
			_matrix.m12, _matrix.m11
		);
	}

	float2x2 MatrixMath::Cofactor(const float2x2& _matrix)
	{
		float2x2 result;
		Cofactor(result.asArray, Minor(_matrix).asArray, FLOAT2X2_SIZE, FLOAT2X2_SIZE);
		return result;
	}

	float2x2 MatrixMath::Adjugate(const float2x2& _matrix)
	{
		return float2x2::Transpose(Cofactor(_matrix));
	}


	float MatrixMath::Determinant(const float3x3& _matrix)
	{
		float result = 0.0f;
		float3x3 cofactor = Cofactor(_matrix);
		for (int i = 0; i < FLOAT3X3_SIZE; i++)
		{
			int index = FLOAT3X3_SIZE * 0 + i;
			result += _matrix.asArray[index] * cofactor[0][i];
		}

		return result;
	}

	float3x3 MatrixMath::Minor(const float3x3& _matrix)
	{
		float3x3 result;

		for (int i = 0; i < FLOAT3X3_SIZE; ++i)
		{
			for (int j = 0; j < FLOAT3X3_SIZE; ++j)
			{
				result[i][j] = Determinant(Cut(_matrix, i, j));
			}
		}

		return result;
	}

	float3x3 MatrixMath::Cofactor(const float3x3& _matrix)
	{
		float3x3 result;
		Cofactor(result.asArray, Minor(_matrix).asArray, FLOAT3X3_SIZE, FLOAT3X3_SIZE);
		return result;
	}

	float3x3 MatrixMath::Adjugate(const float3x3& _matrix)
	{
		return float3x3::Transpose(Cofactor(_matrix));
	}

	float MatrixMath::Determinant(const float4x4& _matrix)
	{
		float result = 0.0f;

		float4x4 cofactor = Cofactor(_matrix);
		for (int j = 0; j < FLOAT4X4_SIZE; ++j)
		{
			result += _matrix.asArray[FLOAT4X4_SIZE * 0 + j] * cofactor[0][j];
		}

		return result;
	}

	float3x3 MatrixMath::Cut(const float4x4& _matrix, int _row, int _col)
	{
		float3x3 result;
		int index = 0;

		for (int i = 0; i < FLOAT4X4_SIZE; ++i)
		{
			for (int j = 0; j < FLOAT4X4_SIZE; ++j)
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

	float4x4 MatrixMath::Minor(const float4x4& _matrix)
	{
		float4x4 result;

		for (int i = 0; i < FLOAT4X4_SIZE; ++i)
		{
			for (int j = 0; j < FLOAT4X4_SIZE; ++j)
			{
				result[i][j] = Determinant(Cut(_matrix, i, j));
			}
		}

		return result;
	}

	float4x4 MatrixMath::Cofactor(const float4x4& _matrix)
	{
		float4x4 result;
		Cofactor(result.asArray, Minor(_matrix).asArray, 4, 4);
		return result;
	}

	float4x4 MatrixMath::Adjugate(const float4x4& _matrix)
	{
		return float4x4::Transpose(Cofactor(_matrix));
	}

	float4x4 MatrixMath::XRotation(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return float4x4(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, cosf(_angle), sinf(_angle), 0.0f,
			0.0f, -sinf(_angle), cos(_angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	float4x4 MatrixMath::YRotation(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return float4x4(
			cosf(_angle), 0.0f, -sinf(_angle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			sinf(_angle), 0.0f, cosf(_angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	float4x4 MatrixMath::ZRotation(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return float4x4(
			cosf(_angle), sinf(_angle), 0.0f, 0.0f,
			-sinf(_angle), cosf(_angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}

	float3x3 MatrixMath::XRotation3X3(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return float3x3(
			1.0f, 0.0f, 0.0f,
			0.0f, cosf(_angle), sinf(_angle),
			0.0f, -sinf(_angle), cos(_angle)
		);
	}

	float3x3 MatrixMath::YRotation3X3(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return float3x3(
			cosf(_angle), 0.0f, -sinf(_angle),
			0.0f, 1.0f, 0.0f,
			sinf(_angle), 0.0f, cosf(_angle)
		);
	}

	float3x3 MatrixMath::ZRotation3X3(float _angle)
	{
		_angle = DEG2RAD(_angle);
		return float3x3(
			cosf(_angle), sinf(_angle), 0.0f,
			-sinf(_angle), cosf(_angle), 0.0f,
			0.0f, 0.0f, 1.0f
		);
	}
}