#include "SphereCollider.h"

#include <components/Transform.h>

namespace CycloneEngine
{
	SphereCollider::SphereCollider(GameObject* _owner, float _radius) : ICollider(_owner)
	{
		center = float3();
		radius = _radius;
	}

	float3 SphereCollider::ClosestPoint(float3& _point)
	{
		float3 sphereToPoint = _point - WorldCenter();
		sphereToPoint = float3::Normalized(sphereToPoint) * radius;

		return sphereToPoint + WorldCenter();
	}

	bool SphereCollider::Overlaps(float3& _point)
	{
		float sqMag = (_point - WorldCenter()).MagnitudeSq();
		float radSq = radius * radius;

		return sqMag < radSq;
	}

	bool SphereCollider::CollidesWith(ICollider* _other)
	{
		if (SphereCollider* otherSphere = dynamic_cast<SphereCollider*>(_other))
		{
			float radiusSum = radius + otherSphere->radius;

			float sqDist = (WorldCenter() - otherSphere->WorldCenter()).MagnitudeSq();

			return sqDist < radiusSum * radiusSum;
		}
	}
}
