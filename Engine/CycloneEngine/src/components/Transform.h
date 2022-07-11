#ifndef CYCLONE_TRANSFORM
#define CYCLONE_TRANSFORM

#include <float3.h>
#include <quaternion.h>
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
		quaternion rotation;
		float3 lossyScale;
		float3 localPosition;
		quaternion localRotation;
		float3 localScale;
		
		float3 EulerAngles() const;
		float3 LocalEulerAngles() const;

		float4x4 LocalToWorldRotation() const;
		float4x4 WorldToLocalRotation() const;
		
	protected:
		void Update() override;
		
	private:
		Transform* m_parentTransform = nullptr;
		float4x4 m_matrix;

	};
}

#endif // !CYCLONE_TRANSFORM