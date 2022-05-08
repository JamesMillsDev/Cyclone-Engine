#include "editor.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "engine/input.h"
#include "engine/debug.h"

#include "windows/console_window.h"
#include "windows/scene_window.h"

#include <GLFW/glfw3.h>

#include "editor_settings.h"
#include "windows/menu_window.h"

using namespace CycloneEngine;

namespace CycloneEditor
{
	editor::editor(GLFWwindow* _window) : settings(new editor_settings())
	{
		windows.push_back(new menu_window(_window));
		windows.push_back(new console_window());
		windows.push_back(new scene_window());
	}

	void editor::init(GLFWwindow* _window) const
	{
		settings->deserialize(_window);

		input::init(_window);

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

	void editor::run() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (editor_window* window : windows)
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

		input::update();
	}

	void editor::cleanup(GLFWwindow* _window) const
	{
		settings->serialize(_window);

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}