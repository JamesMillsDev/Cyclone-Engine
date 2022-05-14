#ifndef CYCLONE_TRANSFORM
#define CYCLONE_TRANSFORM

#include "Component.h"

namespace CycloneEngine
{
	class Transform : public Component
	{
	public:


	private:
		Matrix4x4 localToWorldMatrix;

	};
}

#endif // !CYCLONE_TRANSFORM