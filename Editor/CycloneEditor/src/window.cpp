#include "Window.h"

#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

#include "Debug.h"
#include "../resource.h"

namespace CycloneEditor
{
	Window::Window(const char* _name)
		: windowInstance(nullptr), name(_name), editorInstance(nullptr)
	{

	}

	bool Window::init()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			return false;
		}

		/* Create a windowed mode window and its OpenGL context */
		windowInstance = glfwCreateWindow(640, 480, name, nullptr, nullptr);
		if (!windowInstance)
		{
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(windowInstance);

		/* Start GLEW extension handler */
		if (glewInit())
		{
			return false;
		}

		/* Tell GL to only draw onto a pixel if the shape is closer to the viewer */
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		HINSTANCE hInstance = GetModuleHandle(NULL);
		HWND hWnd = FindWindowA(NULL, "Cyclone Engine");
		HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MAINICON));
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

		editorInstance = new CycloneEditor::Editor(windowInstance);
		editorInstance->init(windowInstance);

		return true;
	}

	void Window::run() const
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(windowInstance))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			editorInstance->run();

			/* Swap front and back buffers */
			glfwSwapBuffers(windowInstance);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	void Window::cleanup() const
	{
		editorInstance->cleanup(windowInstance);

		glfwDestroyWindow(windowInstance);
		glfwTerminate();
	}
}