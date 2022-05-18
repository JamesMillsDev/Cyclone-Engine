#ifndef CYCLONE_TRANSFORM
#define CYCLONE_TRANSFORM

#include <Matrix4x4.h>
#include <Vector3.h>
#include <Quaternion.h>

#include "CycloneEngine.h"
#include "Component.h"

namespace CycloneEngine
{
	class Transform : public Component
	{
	public:
		CYCLONE_DLL Vector3 position() const;
		CYCLONE_DLL Quaternion rotation() const;
		CYCLONE_DLL Vector3 lossyScale() const;
		CYCLONE_DLL Vector3 eulerAngles() const;

		CYCLONE_DLL Vector3 localPosition() const;
		CYCLONE_DLL Quaternion localRotation() const;
		CYCLONE_DLL Vector3 localScale() const;
		CYCLONE_DLL Vector3 localEulerAngles() const;

		CYCLONE_DLL void setPosition(const Vector3 _position);
		CYCLONE_DLL void setRotation(const Quaternion _rotation);
		CYCLONE_DLL void setLossyScale(const Vector3 _scale);
		CYCLONE_DLL void setEulerAngles(const Vector3 _rotation);
		
		CYCLONE_DLL void setLocalPosition(const Vector3 _position);
		CYCLONE_DLL void setLocalRotation(const Quaternion _rotation);
		CYCLONE_DLL void setLocalScale(const Vector3 _scale);
		CYCLONE_DLL void setLocalEulerAngles(const Vector3 _rotation);

		CYCLONE_DLL void setParent(Transform* _parent);
		CYCLONE_DLL Transform* parent() const;

	private:
		Matrix4x4 localToWorldMatrix;
		Matrix4x4 worldToLocalMatrix;
		Transform* parentTransform;

	};
}

#endif // !CYCLONE_TRANSFORM