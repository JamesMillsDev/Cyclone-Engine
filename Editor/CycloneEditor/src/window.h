#ifndef CYCLONE_WINDOW
#define CYCLONE_WINDOW
#include "Editor.h"

namespace CycloneEditor
{
	class Window
	{
	public:
		Window(const char* _name);
		bool Init();
		void Run() const;
		void Cleanup() const;

		GLFWwindow* GetWindowInstance() const { return m_windowInstance; }

	private:
		GLFWwindow* m_windowInstance;
		const char* m_name;
		Editor* m_editorInstance;

	};
}

#endif // !CYCLONE_WINDOW