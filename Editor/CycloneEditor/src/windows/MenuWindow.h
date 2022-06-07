#ifndef CYCLONE_MENU_WINDOW
#define CYCLONE_MENU_WINDOW
#include "EditorWindow.h"

class GLFWwindow;

namespace CycloneEditor
{
	class MenuWindow final : public EditorWindow
	{
	public:
		explicit MenuWindow(GLFWwindow* _window) : m_windowInstance(_window) {}
		void Render() const override;

	private:
		GLFWwindow* m_windowInstance;
	};
}
#endif // !CYCLONE_MENU_WINDOW