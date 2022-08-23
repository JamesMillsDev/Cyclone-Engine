#ifndef CYCLONE_EDITOR_SETTINGS
#define CYCLONE_EDITOR_SETTINGS

#include <float2.h>
#include <string>

class GLFWwindow;

using CycloneEngine::float2;

using std::string;

namespace CycloneEditor
{
	class EditorSettings
	{
	public:
		EditorSettings() = default;

		void Serialize(GLFWwindow* _window) const;
		void Deserialize(GLFWwindow* _window) const;

		float2 GetLastWindowPos() const { return windowPos; }
		float2 GetLastWindowSize() const { return windowSize; }

	private:
		string GetFilePath() const;
		float2 windowPos;
		float2 windowSize;

	};
}

#endif // CYCLONE_EDITOR_SETTINGS