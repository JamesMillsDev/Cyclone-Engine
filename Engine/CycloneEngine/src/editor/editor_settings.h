#ifndef CYCLONE_EDITOR_SETTINGS
#define CYCLONE_EDITOR_SETTINGS

#include <string>

#include <glm/vec2.hpp>

using glm::vec2;

class GLFWwindow;

namespace CycloneEditor
{
	class editor_settings
	{
	public:
		editor_settings() = default;

		void serialize(GLFWwindow* _window) const;
		void deserialize(GLFWwindow* _window) const;

		vec2 get_last_window_pos() const { return windowPos; }
		vec2 get_last_window_size() const { return windowSize; }

	private:
		std::string get_file_path() const;
		vec2 windowPos;
		vec2 windowSize;

	};
}

#endif // CYCLONE_EDITOR_SETTINGS