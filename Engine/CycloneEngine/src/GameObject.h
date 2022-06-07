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

	protected:
		Transform* m_transform = nullptr;
		
	private:
		Components m_components;

	};
}

#endif // !CYCLONE_ENGINE_GAMEOBJECT