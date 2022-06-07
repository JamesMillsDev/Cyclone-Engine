#ifndef CYCLONE_COMPONENT
#define CYCLONE_COMPONENT

namespace CycloneEngine
{
	class Component
	{
	public:
		const char* GetName() const { return m_name; }

	private:
		const char* m_name = nullptr;

	};
}

#endif // !CYCLONE_COMPONENT