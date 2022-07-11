#include "BoxCollider.h"

namespace CycloneEngine
{
	BoxCollider::BoxCollider(GameObject* _owner) : ICollider(_owner)
	{
		size = float3(1);
	}

	float3 BoxCollider::ClosestPoint(float3& _point)
	{
		return float3();
	}

	bool BoxCollider::Overlaps(float3& _point)
	{
		return false;
	}

	bool BoxCollider::CollidesWith(ICollider* _other)
	{
		return false;
	}
}