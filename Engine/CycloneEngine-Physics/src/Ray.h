#ifndef CYLCONE_ENGINE_RAY
#define CYLCONE_ENGINE_RAY

#include <float3.h>

namespace CycloneEngine
{
	typedef struct Ray
	{
		float3 origin;
		float3 direction;

		inline Ray() : direction(0, 0, 1) {}
		inline Ray(const float3& _origin, const float3& _direction)
			: origin(_origin), direction(_direction) {}

		void NormalizeDirection();
		static Ray FromPoints(const float3& _from, const float3& _to);

	} Ray;
}

#endif // !CYLCONE_ENGINE_RAY