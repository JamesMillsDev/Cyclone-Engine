#ifndef CYCLONE_EDITOR
#define CYCLONE_EDITOR

#include <vector>

class GLFWwindow;

namespace CycloneEditor
{
	class editor_window;
	class editor_settings;

	class editor
	{
	public:
		editor(GLFWwindow* _window);

		void init(GLFWwindow* _window) const;
		void run() const;
		void cleanup(GLFWwindow* _window) const;

	private:
		std::vector<editor_window*> windows;
		editor_settings* settings;

	};
}

#endif // !CYCLONE_EDITOR