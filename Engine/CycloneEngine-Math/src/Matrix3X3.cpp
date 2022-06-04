#include "Matrix3X3.h"

#include "Mathf.h"

namespace CycloneEngine
{
    Matrix3X3 Matrix3X3::Transpose(const Matrix3X3& _matrix)
    {
        Matrix3X3 result;
        Mathf::Transpose(_matrix.asArray, result.asArray, MATRIX_3_SIZE, MATRIX_3_SIZE);        
        return result;
    }
}