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

#include "Gizmos.h"
#include "SceneCamera.h"

using namespace CycloneEngine;

namespace CycloneEditor
{
    Editor::Editor(GLFWwindow* _window) : m_settings(new EditorSettings())
    {
        m_windows.push_back(new MenuWindow(_window));
        m_windows.push_back(new ConsoleWindow());

        int w = 0;
        int h = 0;
        glfwGetWindowSize(_window, &w, &h);
        m_camera = new SceneCamera(w, h);
    }

    void Editor::Init(GLFWwindow* _window) const
    {
        m_settings->Deserialize(_window);
	    Gizmos::Create(10000, 10000, 10000, 10000);

        input = new Input();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    void Editor::Run(GLFWwindow* _window) const
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        Gizmos::Clear();

        constexpr glm::vec4 white(1);
        constexpr glm::vec4 black(0, 0, 0, 1);
        for (int i = 0; i < 21; ++i) {
            Gizmos::AddLine(glm::vec3(-10 + i, 0, 10),
                            glm::vec3(-10 + i, 0, -10),
                            i == 10 ? white : black);
            Gizmos::AddLine(glm::vec3(10, 0, -10 + i),
                            glm::vec3(-10, 0, -10 + i),
                            i == 10 ? white : black);
        }

        for(const EditorWindow* window : m_windows)
        {
            window->Render();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        const ImGuiIO& io = ImGui::GetIO();
        (void) io;
        if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }

        m_camera->Update((float)glfwGetTime());
        
        Gizmos::Draw(*m_camera);
    }

    void Editor::Cleanup(GLFWwindow* _window) const
    {
        m_settings->Serialize(_window);
        Gizmos::Destroy();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}
