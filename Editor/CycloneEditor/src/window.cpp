#include "Window.h"

#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Windows.h>

#include "Debug.h"
#include "Input.h"
#include "../resource.h"

using CycloneEngine::Input;

namespace CycloneEditor
{
	Window::Window(const char* _name)
		: m_windowInstance(nullptr), m_name(_name), m_editorInstance(nullptr)
	{

	}

	bool Window::Init()
	{
		/* Initialize the library */
		if (!glfwInit())
		{
			return false;
		}

		/* Create a windowed mode window and its OpenGL context */
		m_windowInstance = glfwCreateWindow(640, 480, m_name, nullptr, nullptr);
		if (!m_windowInstance)
		{
			glfwTerminate();
			return false;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(m_windowInstance);

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

		glfwSetWindowSizeCallback(m_windowInstance, [](GLFWwindow*, const int _w, const int _h)
		{
			glViewport(0, 0, _w, _h);
		});
		
		Input::CreateInstance(m_windowInstance);

		m_editorInstance = new CycloneEditor::Editor(m_windowInstance);
		m_editorInstance->Init(m_windowInstance);

		return true;
	}

	void Window::Run() const
	{
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(m_windowInstance))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Input::GetInstance()->ClearStatus(m_windowInstance);

			/* Poll for and process events */
			glfwPollEvents();

			m_editorInstance->Run(m_windowInstance);

			/* Swap front and back buffers */
			glfwSwapBuffers(m_windowInstance);
		}
	}

	void Window::Cleanup() const
	{
		Input::DestroyInstance();
		m_editorInstance->Cleanup(m_windowInstance);

		glfwDestroyWindow(m_windowInstance);
		glfwTerminate();
	}
}
