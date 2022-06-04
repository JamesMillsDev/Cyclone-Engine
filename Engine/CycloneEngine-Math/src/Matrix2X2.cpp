#include "Matrix2X2.h"

#include "Mathf.h"

namespace CycloneEngine
{
    Matrix2X2 Matrix2X2::Transpose(const Matrix2X2& _matrix)
    {
        Matrix2X2 result;
        Mathf::Transpose(_matrix.asArray, result.asArray, MATRIX_2_SIZE, MATRIX_2_SIZE);        
        return result;
    }
}
