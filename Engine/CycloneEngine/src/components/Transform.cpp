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
}