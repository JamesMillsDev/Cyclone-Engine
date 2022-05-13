#ifndef CYCLONE_MENU_WINDOW
#define CYCLONE_MENU_WINDOW
#include "EditorWindow.h"

class GLFWwindow;

namespace CycloneEditor
{
	class MenuWindow final : public EditorWindow
	{
	public:
		MenuWindow(GLFWwindow* _window)
			: windowInstance(_window) {}
		void render() const override;

	private:
		GLFWwindow* windowInstance;
	};
}
#endif // !CYCLONE_MENU_WINDOW