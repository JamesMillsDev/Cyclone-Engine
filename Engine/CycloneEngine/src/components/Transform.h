#ifndef CYCLONE_TRANSFORM
#define CYCLONE_TRANSFORM

#include <float3.h>
#include <float4x4.h>

#include "CycloneEngine.h"
#include "Component.h"

namespace CycloneEngine
{
	class Transform : public Component
	{
	public:
		CYCLONE_DLL void SetParent(Transform* _parent);
		CYCLONE_DLL Transform* Parent() const;

		float3 position;
		float3 eulerAngles;
		float3 lossyScale;
		float3 localPosition;
		float3 localEulerAngles;
		float3 localScale;

	private:
		Transform* m_parentTransform = nullptr;

	};
}

#endif // !CYCLONE_TRANSFORM