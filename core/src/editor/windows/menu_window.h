#ifndef CYCLONE_MENU_WINDOW
#define CYCLONE_MENU_WINDOW
#include "editor_window.h"

class GLFWwindow;

namespace CycloneEditor
{
	class menu_window final : public editor_window
	{
	public:
		menu_window(GLFWwindow* _window)
			: windowInstance(_window) {}
		void render() const override;

	private:
		GLFWwindow* windowInstance;
	};
}
#endif // !CYCLONE_MENU_WINDOW