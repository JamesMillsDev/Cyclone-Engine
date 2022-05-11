#ifndef CYCLONE_EDITOR_WINDOW
#define CYCLONE_EDITOR_WINDOW

namespace CycloneEditor
{
	class editor_window
	{
	public:
		virtual ~editor_window() = default;
		virtual void render() const = 0;
		
		bool* isOpen;

	};
}

#endif // !CYCLONE_EDITOR_WINDOW