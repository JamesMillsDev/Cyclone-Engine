#ifndef CYCLONE_EDITOR
#define CYCLONE_EDITOR

#include <vector>

class GLFWwindow;

namespace CycloneEditor
{
	class EditorWindow;
	class EditorSettings;

	class Editor
	{
	public:
		Editor(GLFWwindow* _window);

		void init(GLFWwindow* _window) const;
		void run() const;
		void cleanup(GLFWwindow* _window) const;

	private:
		std::vector<EditorWindow*> windows;
		EditorSettings* settings;

	};
}

#endif // !CYCLONE_EDITOR