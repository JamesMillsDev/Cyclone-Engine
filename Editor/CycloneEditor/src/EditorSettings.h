#ifndef CYCLONE_EDITOR_SETTINGS
#define CYCLONE_EDITOR_SETTINGS

#include <Vector2.h>
#include <string>

class GLFWwindow;

using namespace CycloneEngine;

using std::string;

namespace CycloneEditor
{
	class EditorSettings
	{
	public:
		EditorSettings() = default;

		void Serialize(GLFWwindow* _window) const;
		void Deserialize(GLFWwindow* _window) const;

		Vector2 GetLastWindowPos() const { return windowPos; }
		Vector2 GetLastWindowSize() const { return windowSize; }

	private:
		string GetFilePath() const;
		Vector2 windowPos;
		Vector2 windowSize;

	};
}

#endif // CYCLONE_EDITOR_SETTINGS