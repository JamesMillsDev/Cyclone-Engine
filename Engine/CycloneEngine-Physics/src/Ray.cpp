#include "Ray.h"

namespace CycloneEngine
{
	void Ray::NormalizeDirection()
	{
		direction.Normalize();
	}

	Ray Ray::FromPoints(const float3& _from, const float3& _to)
	{
		return Ray(_from, float3::Normalized(_to - _from));
	}
}
