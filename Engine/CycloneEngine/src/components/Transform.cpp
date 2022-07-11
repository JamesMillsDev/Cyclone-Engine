#include "Transform.h"

namespace CycloneEngine
{
	void Transform::SetParent(Transform* _parent)
	{
		m_parentTransform = _parent;
	}

	Transform* Transform::Parent() const
	{
		return m_parentTransform;
	}

	float3 Transform::EulerAngles() const
	{
		return rotation.EulerAngles();
	}

	float3 Transform::LocalEulerAngles() const
	{
		return localRotation.EulerAngles();
	}

	float4x4 Transform::LocalToWorldRotation() const
	{
		return m_matrix;
	}

	float4x4 Transform::WorldToLocalRotation() const
	{
		return m_parentTransform != nullptr ? m_parentTransform->m_matrix * m_matrix : m_matrix;
	}

	void Transform::Update()
	{
		m_matrix = float4x4::TRS(localPosition, LocalEulerAngles(), localScale);
	}
}
