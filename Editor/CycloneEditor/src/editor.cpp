#include "Editor.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Input.h"
#include "Debug.h"

#include "windows/ConsoleWindow.h"

#include <GLFW/glfw3.h>

#include "EditorSettings.h"
#include "windows/MenuWindow.h"

using namespace CycloneEngine;

namespace CycloneEditor
{
    Editor::Editor(GLFWwindow* _window) : m_settings(new EditorSettings())
    {
        m_windows.push_back(new MenuWindow(_window));
        m_windows.push_back(new ConsoleWindow());
    }

    void Editor::Init(GLFWwindow* _window) const
    {
        m_settings->Deserialize(_window);

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

	void Editor::Run(GLFWwindow* _window) const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (const EditorWindow* window : m_windows)
			window->Render();

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
	}

    void Editor::Cleanup(GLFWwindow* _window) const
    {
        m_settings->Serialize(_window);

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
