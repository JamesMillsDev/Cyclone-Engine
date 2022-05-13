#ifndef CYCLONE_WINDOW
#define CYCLONE_WINDOW
#include "editor.h"

namespace CycloneEditor
{
	class Window
	{
	public:
		Window(const char* _name);
		bool init();
		void run() const;
		void cleanup() const;

	private:
		GLFWwindow* windowInstance;
		const char* name;
		CycloneEditor::Editor* editorInstance;

	};
}

#endif // !CYCLONE_WINDOW