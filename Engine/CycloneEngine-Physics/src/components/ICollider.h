#ifndef CYLCONE_ENGINE_ICOLLIDER
#define CYLCONE_ENGINE_ICOLLIDER

#include "../CyclonePhysics.h"

#include <float3.h>
#include <GameObject.h>
#include <components/Transform.h>
#include <components/Component.h>

namespace CycloneEngine
{
	class ICollider : public Component
	{
	public:
		ICollider(GameObject* _owner) : gameObject(_owner) {};
		virtual float3 ClosestPoint(float3& _point) = 0;
		virtual bool Overlaps(float3& _point) = 0;

		float3 center;
		GameObject* gameObject;

	protected:
		virtual bool CollidesWith(ICollider* _other) = 0;
		float3 WorldCenter() const { return center + gameObject->transform->position; }

	};
}

#endif //!CYLCONE_ENGINE_ICOLLIDER