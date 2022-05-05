#include "window.h"

#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "debug.h"
#include "input.h"

namespace CycloneEngine
{
	window::window(const char* _name) : windowInstance(nullptr), name(_name)
	{

	}

	bool window::init()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			debug::log_error("Unable to initialise GLFW.");
			return false;
		}

		/* Create a windowed mode window and its OpenGL context */
		windowInstance = glfwCreateWindow(640, 480, name, nullptr, nullptr);
		if (!windowInstance)
		{
			debug::log_error("Unable to create window instance.");
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(windowInstance);

		/* Start GLEW extension handler */
		if(glewInit())
		{
			debug::log_error("Unable to initialise GLEW.");
			return false;
		}

		/* Get and log version info */
		const GLubyte* renderer = glGetString(GL_RENDERER);
		const GLubyte* version = glGetString(GL_VERSION);
		std::stringstream rendererStream;
		rendererStream << "Renderer: " << renderer;
		debug::log(rendererStream.str().c_str());

		std::stringstream versionStream;
		versionStream << "OpenGL version supported: " << version;
		debug::log(versionStream.str().c_str());

		/* Tell GL to only draw onto a pixel if the shape is closer to the viewer */
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		return true;
	}

	void window::run() const
	{
		input::init(windowInstance);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(windowInstance))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(windowInstance);

			if (input::keydown(keycode::A))
				debug::log_error("pressed a key");

			input::update();

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	void window::cleanup() const
	{
		glfwTerminate();
	}
}
