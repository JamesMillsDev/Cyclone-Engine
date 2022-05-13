#include "Mathf.h"

namespace CycloneEngine
{
	float Mathf::degToRad = PI * 2.f / 360.f;
	float Mathf::radToDeg = 1.f / Mathf::degToRad;

	float Mathf::clamp(float _val, float _min, float _max)
	{
		if (_val < _min)
			return _min;
		else if (_val > _max)
			return _max;

		return _val;
	}
}