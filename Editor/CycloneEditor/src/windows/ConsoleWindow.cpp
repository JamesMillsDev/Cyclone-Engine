#include "ConsoleWindow.h"

#include "imgui/imgui.h"

#include "Debug.h"
#include "Input.h"

namespace CycloneEditor
{
	void ConsoleWindow::Render() const
	{
		ImGui::Begin("Console");

		for (CycloneEngine::LogMessage* message : CycloneEngine::Debug::GetMessages())
			message->Render();

		ImGui::End();

		if (CycloneEngine::Input::KeyDown(CycloneEngine::Keycode::A))
			CycloneEngine::Debug::LogError("test");
	}
}
