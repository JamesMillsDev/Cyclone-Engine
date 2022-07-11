#ifndef CYLCONE_ENGINE_BOXCOLLIDER
#define CYLCONE_ENGINE_BOXCOLLIDER

#include "ICollider.h"

namespace CycloneEngine
{
	class BoxCollider : public ICollider
	{
	public:
		CYCLONE_DLL BoxCollider(GameObject* _owner);
		CYCLONE_DLL virtual float3 ClosestPoint(float3& _point) override;
		CYCLONE_DLL virtual bool Overlaps(float3& _point) override;

		float3 size;

	protected:
		CYCLONE_DLL virtual bool CollidesWith(ICollider* _other) override;

	};
}

#endif //!CYLCONE_ENGINE_BOXCOLLIDER