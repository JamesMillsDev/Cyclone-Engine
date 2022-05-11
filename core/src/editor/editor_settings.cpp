#include "editor_settings.h"

#include <GLFW/glfw3.h>

#include <filesystem>
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::fstream;

namespace fs = std::filesystem;

namespace CycloneEditor
{
	void editor_settings::serialize(GLFWwindow* _window) const
	{
		std::string path = get_file_path();

		ofstream file;
		file.open(path, std::ios::out | std::ios::binary);

		int xPos;
		int yPos;
		glfwGetWindowPos(_window, &xPos, &yPos);
		file.write((char*)&xPos, sizeof(int));
		file.write((char*)&yPos, sizeof(int));

		int xSize;
		int ySize;
		glfwGetWindowSize(_window, &xSize, &ySize);
		file.write((char*)&xSize, sizeof(int));
		file.write((char*)&ySize, sizeof(int));

		int maximized = glfwGetWindowAttrib(_window, GLFW_MAXIMIZED);
		file.write((char*)&maximized, sizeof(int));

		file.close();
	}

	void editor_settings::deserialize(GLFWwindow* _window) const
	{
		std::string path = get_file_path();

		ifstream file;
		file.open(path, std::ios::in | std::ios::binary);
		if (!file.good())
			return;

		int xPos = 0;
		int yPos = 0;
		file.read((char*)&xPos, sizeof(int));
		file.read((char*)&yPos, sizeof(int));
		glfwSetWindowPos(_window, xPos, yPos);

		int xSize = 0;
		int ySize = 0;
		file.read((char*)&xSize, sizeof(int));
		file.read((char*)&ySize, sizeof(int));
		glfwSetWindowSize(_window, xSize, ySize);

		int maximized = 0;
		file.read((char*)&maximized, sizeof(int));
		if (maximized == 1)
			glfwMaximizeWindow(_window);

		file.close();
	}

	std::string editor_settings::get_file_path() const
	{
		std::string path = getenv("localappdata");
		path += "\\CycloneEngine";
		if(!fs::is_directory(path) || !fs::exists(path))
		{
			fs::create_directory(path);
		}

		path += "\\app.settings";

		return path;
	}
}