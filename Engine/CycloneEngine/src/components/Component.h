#ifndef CYCLONE_COMPONENT
#define CYCLONE_COMPONENT

namespace CycloneEngine
{
	class Component
	{
	public:
		const char* getName() const { return name; }

	private:
		const char* name;

	};
}

#endif // !CYCLONE_COMPONENT