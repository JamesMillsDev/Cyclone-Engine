#include "Matrix4X4.h"

#include "Mathf.h"

namespace CycloneEngine
{
    Matrix4X4 Matrix4X4::Transpose(const Matrix4X4& _matrix)
    {
        Matrix4X4 result;
        Mathf::Transpose(_matrix.asArray, result.asArray, MATRIX_4_SIZE, MATRIX_4_SIZE);        
        return result;
    }
}