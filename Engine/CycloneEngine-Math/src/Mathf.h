#ifndef CYCLONE_MATH_MATHF
#define CYCLONE_MATH_MATHF

#include "CycloneMath.h"

namespace CycloneEngine
{
#define PI 3.14159265358979

	class Mathf
	{
	public:
		static float degToRad;
		static float radToDeg;

		CYCLONE_DLL static float clamp(float _val, float _min, float _max);
	};
}

#endif //!CYCLONE_MATH_MATHF