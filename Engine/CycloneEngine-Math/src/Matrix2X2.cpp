#include "Matrix2X2.h"

#include "Mathf.h"
#include "MatrixMath.h"

namespace CycloneEngine
{
    Matrix2X2 Matrix2X2::Transpose(const Matrix2X2& _matrix)
    {
        Matrix2X2 result;
        MatrixMath::Transpose(_matrix.asArray, result.asArray, MATRIX_2_SIZE, MATRIX_2_SIZE);
        return result;
    }

    Matrix2X2 Matrix2X2::Inverse(const Matrix2X2& _matrix)
    {
        float det = MatrixMath::Determinant(_matrix);
        if (CMP(det, 0.0f))
            return Matrix2X2();

        return MatrixMath::Adjugate(_matrix) * (1.0f / det);
    }

    Matrix2X2 operator*(const Matrix2X2& _matrix, float _scalar)
    {
        Matrix2X2 result;
        for (int i = 0; i < MATRIX_2_SIZE; ++i) 
        {
            result.asArray[i] = _matrix.asArray[i] * _scalar;
        }
        return result;
    }

    Matrix2X2 operator*(const Matrix2X2& _matrix, const Matrix2X2& _other)
    {
        Matrix2X2 result;
        MatrixMath::Multiply(result.asArray, _matrix.asArray, MATRIX_2_SIZE, MATRIX_2_SIZE, _other.asArray, MATRIX_2_SIZE, MATRIX_2_SIZE);
        return result;
    }
}
