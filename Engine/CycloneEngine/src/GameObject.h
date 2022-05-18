#ifndef CYCLONE_ENGINE_GAMEOBJECT
#define CYCLONE_ENGINE_GAMEOBJECT

#include <vector>

namespace CycloneEngine
{
	class Component;
	class Transform;

	typedef std::vector<Component*> Components;

	class GameObject
	{
	public:

	private:
		Transform* transform;
		Components components;

	};
}

#endif // !CYCLONE_ENGINE_GAMEOBJECT