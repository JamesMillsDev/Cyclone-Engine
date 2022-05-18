#include "Transform.h"

namespace CycloneEngine
{
	Vector3 Transform::position() const 
	{ 
		return worldToLocalMatrix.getTranslation(); 
	}

	Quaternion Transform::rotation() const
	{
		return worldToLocalMatrix.getRotation();
	}

	Vector3 Transform::lossyScale() const
	{
		return worldToLocalMatrix.getScale();
	}

	Vector3 Transform::eulerAngles() const
	{
		return worldToLocalMatrix.getEuler();
	}

	Vector3 Transform::localPosition() const
	{
		return localToWorldMatrix.getTranslation();
	}

	Quaternion Transform::localRotation() const
	{
		return localToWorldMatrix.getRotation();
	}

	Vector3 Transform::localScale() const
	{
		return localToWorldMatrix.getScale();
	}

	Vector3 Transform::localEulerAngles() const
	{
		return localToWorldMatrix.getEuler();
	}

	void Transform::setPosition(const Vector3 _position)
	{
		worldToLocalMatrix.setTranslation(_position);
	}

	void Transform::setRotation(const Quaternion _rotation)
	{
		worldToLocalMatrix.setRotation(_rotation);
	}

	void Transform::setLossyScale(const Vector3 _scale)
	{
		worldToLocalMatrix.setScale(_scale);
	}

	void Transform::setEulerAngles(const Vector3 _rotation)
	{
		worldToLocalMatrix.setEuler(_rotation);
	}

	void Transform::setLocalPosition(const Vector3 _position)
	{
		localToWorldMatrix.setTranslation(_position);
	}

	void Transform::setLocalRotation(const Quaternion _rotation)
	{
		localToWorldMatrix.setRotation(_rotation);
	}

	void Transform::setLocalScale(const Vector3 _scale)
	{
		localToWorldMatrix.setScale(_scale);
	}

	void Transform::setLocalEulerAngles(const Vector3 _rotation)
	{
		localToWorldMatrix.setEuler(_rotation);
	}

	void Transform::setParent(Transform* _parent)
	{
		parentTransform = _parent;
	}

	Transform* Transform::parent() const
	{
		return parentTransform;
	}
}