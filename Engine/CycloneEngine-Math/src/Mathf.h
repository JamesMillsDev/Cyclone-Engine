#ifndef CYCLONE_MATH_MATHF
#define CYCLONE_MATH_MATHF

#include "CycloneMath.h"

#include <cmath>
#include <cfloat>

namespace CycloneEngine
{
#define PI 3.14159265358979
#define CMP(x, y) (fabsf((x)-(y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))

	class Mathf
	{
	public:
		static float degToRad;
		static float radToDeg;

		CYCLONE_DLL static float Clamp(float _val, float _min, float _max);
		CYCLONE_DLL static void Transpose(const float *_srcMat, float *_dstMat, int _srcRows, int _srcCols);
	};
}

#endif //!CYCLONE_MATH_MATHF