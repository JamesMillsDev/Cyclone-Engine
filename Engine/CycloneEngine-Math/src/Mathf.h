#ifndef CYCLONE_MATH_MATHF
#define CYCLONE_MATH_MATHF

#include <cmath>
#include <cfloat>

namespace CycloneEngine
{
#define PI 3.14159265358979f
#define CMP(x, y) (fabsf((x)-(y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))
#define DEG2RAD(x) ((x) * 0.0174533f)

	class Mathf
	{
	public:
		static float degToRad;
		static float radToDeg;

		static float Clamp(float _val, float _min, float _max);
	};
}

#endif //!CYCLONE_MATH_MATHF