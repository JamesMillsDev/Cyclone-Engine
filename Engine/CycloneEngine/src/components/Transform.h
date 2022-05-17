#ifndef CYCLONE_TRANSFORM
#define CYCLONE_TRANSFORM

#include <Matrix4x4.h>
#include <Vector3.h>
#include <Quaternion.h>

#include "Component.h"

namespace CycloneEngine
{
	class Transform : public Component
	{
	public:
		void setPosition(const Vector3 _position) { worldToLocalMatrix.setTranslation(_position); }
		Vector3 position() const { return worldToLocalMatrix.getTranslation(); }
		Quaternion rotation() const { return worldToLocalMatrix.getRotation(); }
		Vector3 lossyScale() const { return worldToLocalMatrix.getScale(); }
		Vector3 euler() const { return worldToLocalMatrix.getEuler(); }

		void setLocalPosition(const Vector3 _position) { localToWorldMatrix.setTranslation(_position); }
		Vector3 localPosition() const { return localToWorldMatrix.getTranslation(); }
		Quaternion localRotation() const { return localToWorldMatrix.getRotation(); }
		Vector3 localScale() const { return localToWorldMatrix.getScale(); }
		Vector3 localEuler() const { return localToWorldMatrix.getEuler(); }

	private:
		Matrix4x4 localToWorldMatrix;
		Matrix4x4 worldToLocalMatrix;

	};
}

#endif // !CYCLONE_TRANSFORM