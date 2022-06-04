#include "Transform.h"

namespace CycloneEngine
{
	Vector3 Transform::Position() const 
	{ 
		return worldToLocalMatrix.getTranslation(); 
	}

	Quaternion Transform::Rotation() const
	{
		return worldToLocalMatrix.getRotation();
	}

	Vector3 Transform::LossyScale() const
	{
		return worldToLocalMatrix.getScale();
	}

	Vector3 Transform::EulerAngles() const
	{
		return worldToLocalMatrix.getEuler();
	}

	Vector3 Transform::LocalPosition() const
	{
		return localToWorldMatrix.getTranslation();
	}

	Quaternion Transform::LocalRotation() const
	{
		return localToWorldMatrix.getRotation();
	}

	Vector3 Transform::LocalScale() const
	{
		return localToWorldMatrix.getScale();
	}

	Vector3 Transform::LocalEulerAngles() const
	{
		return localToWorldMatrix.getEuler();
	}

	void Transform::SetPosition(const Vector3 _position)
	{
		worldToLocalMatrix.setTranslation(_position);
	}

	void Transform::SetRotation(const Quaternion _rotation)
	{
		worldToLocalMatrix.setRotation(_rotation);
	}

	void Transform::SetLossyScale(const Vector3 _scale)
	{
		worldToLocalMatrix.setScale(_scale);
	}

	void Transform::SetEulerAngles(const Vector3 _rotation)
	{
		worldToLocalMatrix.setEuler(_rotation);
	}

	void Transform::SetLocalPosition(const Vector3 _position)
	{
		localToWorldMatrix.setTranslation(_position);
	}

	void Transform::SetLocalRotation(const Quaternion _rotation)
	{
		localToWorldMatrix.setRotation(_rotation);
	}

	void Transform::SetLocalScale(const Vector3 _scale)
	{
		localToWorldMatrix.setScale(_scale);
	}

	void Transform::SetLocalEulerAngles(const Vector3 _rotation)
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