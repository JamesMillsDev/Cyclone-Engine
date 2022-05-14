#ifndef CYCLONE_EDITOR_SETTINGS
#define CYCLONE_EDITOR_SETTINGS

#include <string>

#include <glm/vec2.hpp>

using glm::vec2;

class GLFWwindow;

namespace CycloneEditor
{
	class EditorSettings
	{
	public:
		EditorSettings() = default;

		void serialize(GLFWwindow* _window) const;
		void deserialize(GLFWwindow* _window) const;

		vec2 getLastWindowPos() const { return windowPos; }
		vec2 getLastWindowSize() const { return windowSize; }

	private:
		std::string getFilePath() const;
		vec2 windowPos;
		vec2 windowSize;

	};
}

#endif // CYCLONE_EDITOR_SETTINGS