#ifndef CYLCONE_ENGINE_SPHERECOLLIDER
#define CYLCONE_ENGINE_SPHERECOLLIDER

#include "ICollider.h"

namespace CycloneEngine
{
	class SphereCollider : public ICollider
	{
	public:
		CYCLONE_DLL SphereCollider(GameObject* _owner, float _radius);
		CYCLONE_DLL virtual float3 ClosestPoint(float3& _point) override;
		CYCLONE_DLL virtual bool Overlaps(float3& _point) override;

		float radius;

	protected:
		CYCLONE_DLL virtual bool CollidesWith(ICollider* _other) override;

	};
}

#endif //!CYLCONE_ENGINE_SPHERECOLLIDER