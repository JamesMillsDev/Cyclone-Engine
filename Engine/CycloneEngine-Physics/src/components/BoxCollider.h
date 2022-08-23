#ifndef CYLCONE_ENGINE_BOXCOLLIDER
#define CYLCONE_ENGINE_BOXCOLLIDER

#include "ICollider.h"

namespace CycloneEngine
{
	class BoxCollider : public ICollider
	{
	public:
		BoxCollider(GameObject* _owner);
		virtual float3 ClosestPoint(float3& _point) override;
		virtual bool Overlaps(float3& _point) override;

		float3 size;

	protected:
		virtual bool CollidesWith(ICollider* _other) override;

	};
}

#endif //!CYLCONE_ENGINE_BOXCOLLIDER