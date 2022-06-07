#include "Transform.h"

namespace CycloneEngine
{
	float3 Transform::Position() const 
	{ 
		return worldToLocalMatrix.getTranslation(); 
	}

	Quaternion Transform::Rotation() const
	{
		return worldToLocalMatrix.getRotation();
	}

	float3 Transform::LossyScale() const
	{
		return worldToLocalMatrix.getScale();
	}

	float3 Transform::EulerAngles() const
	{
		return worldToLocalMatrix.getEuler();
	}

	float3 Transform::LocalPosition() const
	{
		return localToWorldMatrix.getTranslation();
	}

	Quaternion Transform::LocalRotation() const
	{
		return localToWorldMatrix.getRotation();
	}

	float3 Transform::LocalScale() const
	{
		return localToWorldMatrix.getScale();
	}

	float3 Transform::LocalEulerAngles() const
	{
		return localToWorldMatrix.getEuler();
	}

	void Transform::SetPosition(const float3 _position)
	{
		worldToLocalMatrix.setTranslation(_position);
	}

	void Transform::SetRotation(const Quaternion _rotation)
	{
		worldToLocalMatrix.setRotation(_rotation);
	}

	void Transform::SetLossyScale(const float3 _scale)
	{
		worldToLocalMatrix.setScale(_scale);
	}

	void Transform::SetEulerAngles(const float3 _rotation)
	{
		worldToLocalMatrix.setEuler(_rotation);
	}

	void Transform::SetLocalPosition(const float3 _position)
	{
		localToWorldMatrix.setTranslation(_position);
	}

	void Transform::SetLocalRotation(const Quaternion _rotation)
	{
		localToWorldMatrix.setRotation(_rotation);
	}

	void Transform::SetLocalScale(const float3 _scale)
	{
		localToWorldMatrix.setScale(_scale);
	}

	void Transform::SetLocalEulerAngles(const float3 _rotation)
	{
		localToWorldMatrix.setEuler(_rotation);
	}

	void Transform::SetParent(Transform* _parent)
	{
		parentTransform = _parent;
	}

	Transform* Transform::Parent() const
	{
		return parentTransform;
	}
}