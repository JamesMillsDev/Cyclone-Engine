#ifndef CYCLONE_EDITOR
#define CYCLONE_EDITOR

#include <vector>

class GLFWwindow;

using std::vector;

namespace CycloneEditor
{
	class EditorWindow;
	class EditorSettings;

	typedef vector<EditorWindow*> WindowCollection;

	class Editor
	{
	public:
		explicit Editor(GLFWwindow* _window);

		void Init(GLFWwindow* _window) const;
		void Run(GLFWwindow* _window) const;
		void Cleanup(GLFWwindow* _window) const;

	private:
		WindowCollection m_windows;
		EditorSettings* m_settings;

	};
}

#endif // !CYCLONE_EDITOR