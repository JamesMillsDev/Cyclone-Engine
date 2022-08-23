#ifndef CYLCONE_ENGINE_SPHERECOLLIDER
#define CYLCONE_ENGINE_SPHERECOLLIDER

#include "ICollider.h"

namespace CycloneEngine
{
	class SphereCollider : public ICollider
	{
	public:
		SphereCollider(GameObject* _owner, float _radius);
		virtual float3 ClosestPoint(float3& _point) override;
		virtual bool Overlaps(float3& _point) override;

		float radius;

	protected:
		virtual bool CollidesWith(ICollider* _other) override;

	};
}

#endif //!CYLCONE_ENGINE_SPHERECOLLIDER