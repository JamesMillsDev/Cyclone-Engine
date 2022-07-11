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

		ImGui::SetScrollHereY(1.0f);

		ImGui::End();
	}
}
