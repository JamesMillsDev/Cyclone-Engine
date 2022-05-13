#include "Editor.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "input.h"
#include "debug.h"

#include "windows/ConsoleWindow.h"
#include "windows/SceneWindow.h"

#include <GLFW/glfw3.h>

#include "EditorSettings.h"
#include "windows/MenuWindow.h"

using namespace CycloneEngine;

namespace CycloneEditor
{
	Editor::Editor(GLFWwindow* _window) : settings(new EditorSettings())
	{
		windows.push_back(new MenuWindow(_window));
		windows.push_back(new ConsoleWindow());
		windows.push_back(new SceneWindow());
	}

	void Editor::init(GLFWwindow* _window) const
	{
		settings->deserialize(_window);

		Input::init(_window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(_window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
	}

	void Editor::run() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (EditorWindow* window : windows)
		{
			window->render();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}

		Input::update();
	}

	void Editor::cleanup(GLFWwindow* _window) const
	{
		settings->serialize(_window);

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}