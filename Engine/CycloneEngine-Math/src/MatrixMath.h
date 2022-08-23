#ifndef CYCLONE_MATH_MATRIX_MATH
#define CYCLONE_MATH_MATRIX_MATH

#include "float2x2.h"
#include "float3x3.h"
#include "float4x4.h"

namespace CycloneEngine
{
	class MatrixMath
	{
	public:
		static bool Multiply(float* _out, const float* _matA, int _aRows, int _aCols, const float* _matB, int _bRows, int _bCols);
		static void Transpose(const float* _srcMat, float* _dstMat, int _srcRows, int _srcCols);
		static void Cofactor(float* _out, const float* _minor, int _rows, int _cols);

		static float Determinant(const float2x2& _matrix);
		static float2x2 Cut(const float3x3& _matrix, int _row, int _col);
		static float2x2 Minor(const float2x2& _matrix);
		static float2x2 Cofactor(const float2x2& _matrix);
		static float2x2 Adjugate(const float2x2& _matrix);

		static float Determinant(const float3x3& _matrix);
		static float3x3 Minor(const float3x3& _matrix);
		static float3x3 Cofactor(const float3x3& _matrix);
		static float3x3 Adjugate(const float3x3& _matrix);

		static float Determinant(const float4x4& _matrix);
		static float3x3 Cut(const float4x4& _matrix, int _row, int _col);
		static float4x4 Minor(const float4x4& _matrix);
		static float4x4 Cofactor(const float4x4& _matrix);
		static float4x4 Adjugate(const float4x4& _matrix);

		static float4x4 XRotation(float _angle);
		static float4x4 YRotation(float _angle);
		static float4x4 ZRotation(float _angle);
		static float3x3 XRotation3X3(float _angle);
		static float3x3 YRotation3X3(float _angle);
		static float3x3 ZRotation3X3(float _angle);
	};
}

#endif