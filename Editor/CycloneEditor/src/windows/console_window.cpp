#include "console_window.h"

#include "imgui/imgui.h"

#include "debug.h"
#include "input.h"

namespace CycloneEditor
{
	void console_window::render() const
	{
		ImGui::Begin("Console");

		for (CycloneEngine::log_message* message : CycloneEngine::debug::get_messages())
			message->render();

		ImGui::End();

		if (CycloneEngine::input::keydown(CycloneEngine::keycode::A))
			CycloneEngine::debug::log_error("test");
	}
}
