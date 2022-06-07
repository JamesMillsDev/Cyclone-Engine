#include "float2x2.h"

#include "Mathf.h"
#include "MatrixMath.h"

namespace CycloneEngine
{
    float2x2 float2x2::Transpose(const float2x2& _matrix)
    {
        float2x2 result;
        MatrixMath::Transpose(_matrix.asArray, result.asArray, FLOAT2X2_SIZE, FLOAT2X2_SIZE);
        return result;
    }

    float2x2 float2x2::Inverse(const float2x2& _matrix)
    {
        float det = MatrixMath::Determinant(_matrix);
        if (CMP(det, 0.0f))
            return float2x2();

        return MatrixMath::Adjugate(_matrix) * (1.0f / det);
    }

    float2x2 operator*(const float2x2& _matrix, float _scalar)
    {
        float2x2 result;
        for (int i = 0; i < FLOAT2X2_SIZE; ++i) 
        {
            result.asArray[i] = _matrix.asArray[i] * _scalar;
        }
        return result;
    }

    float2x2 operator*(const float2x2& _matrix, const float2x2& _other)
    {
        float2x2 result;
        MatrixMath::Multiply(result.asArray, _matrix.asArray, FLOAT2X2_SIZE, FLOAT2X2_SIZE, _other.asArray, FLOAT2X2_SIZE, FLOAT2X2_SIZE);
        return result;
    }
}
