#ifndef CYCLONE_TRANSFORM
#define CYCLONE_TRANSFORM

#include <Vector3.h>

#include "CycloneEngine.h"
#include "Component.h"

namespace CycloneEngine
{
	class Transform : public Component
	{
	public:
		CYCLONE_DLL float3 Position() const;
		CYCLONE_DLL Quaternion Rotation() const;
		CYCLONE_DLL float3 LossyScale() const;
		CYCLONE_DLL float3 EulerAngles() const;

		CYCLONE_DLL float3 LocalPosition() const;
		CYCLONE_DLL Quaternion LocalRotation() const;
		CYCLONE_DLL float3 LocalScale() const;
		CYCLONE_DLL float3 LocalEulerAngles() const;

		CYCLONE_DLL void SetPosition(float3 _position);
		CYCLONE_DLL void SetRotation(Quaternion _rotation);
		CYCLONE_DLL void SetLossyScale(float3 _scale);
		CYCLONE_DLL void SetEulerAngles(float3 _rotation);
		
		CYCLONE_DLL void SetLocalPosition(float3 _position);
		CYCLONE_DLL void SetLocalRotation(Quaternion _rotation);
		CYCLONE_DLL void SetLocalScale(float3 _scale);
		CYCLONE_DLL void SetLocalEulerAngles(float3 _rotation);

		CYCLONE_DLL void SetParent(Transform* _parent);
		CYCLONE_DLL Transform* Parent() const;

	private:
		Matrix4x4 m_localToWorldMatrix;
		Matrix4x4 m_worldToLocalMatrix;
		Transform* m_parentTransform = nullptr;

	};
}

#endif // !CYCLONE_TRANSFORM