#include "Mathf.h"

namespace CycloneEngine
{
    float Mathf::degToRad = PI * 2.0f / 360.0f;
    float Mathf::radToDeg = 1.f / Mathf::degToRad;

    float Mathf::Clamp(const float _val, const float _min, const float _max)
    {
        if(_val < _min)
            return _min;

        if(_val > _max)
            return _max;

        return _val;
    }

    void Mathf::Transpose(const float* _srcMat, float* _dstMat, const int _srcRows, const int _srcCols)
    {
        for(int i = 0; i < _srcRows * _srcCols; i++)
        {
            const int row = i / _srcRows;
            const int col = i % _srcRows;
            _dstMat[i] = _srcMat[_srcCols * col + row];
        }
    }
}
