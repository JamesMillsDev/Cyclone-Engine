#ifndef CYCLONE_COMPONENT
#define CYCLONE_COMPONENT

namespace CycloneEngine
{	
	class Component
	{
	public:
		const char* GetName() const { return m_name; }

	protected:
		virtual void Update() {}
		
	private:
		const char* m_name = nullptr;

		friend class GameObject;

	};
}

#endif // !CYCLONE_COMPONENT