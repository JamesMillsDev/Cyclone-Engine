#include "input.h"

#include <GLFW/glfw3.h>

namespace CycloneEngine
{
	vector<input::key_state> input::keys;

	input::key_state::key_state(const keycode _code) : key(_code), held(false), up(false), down(false)
	{
	}

	void input::init(GLFWwindow* _window)
	{
		glfwSetKeyCallback(_window, key_callback);
	}

	void input::key_callback(GLFWwindow* _window, int _key, int _scancode, const int _action, int _mods)
	{
		keycode code = static_cast<keycode>(_key);
		key_state* key = nullptr;
		for (key_state state : keys)
		{
			if (state.key == code)
			{
				key = &state;
				break;
			}
		}

		if (key == nullptr)
			return;

		if (_action == GLFW_PRESS)
		{
			key->down = true;
			key->held = true;
		}
		else if(_action == GLFW_REPEAT)
		{
			key->down = false;
			key->held = true;
		}
		else if(_action == GLFW_RELEASE)
		{
			key->up = true;
			key->held = true;
		}
	}

	void input::update()
	{
		for (key_state& state : keys)
		{
			if (state.up && state.held)
				state.up = false;
		}
	}

	bool input::keyup(const keycode _code)
	{
		key_state state = keys.at(_code);
		if (state == nullptr)
			return false;

		return state->up;
	}

	bool input::keydown(const keycode _code)
	{
		key_state* state = keys.at(_code);
		if (state == nullptr)
			return false;

		return state->down;
	}

	bool input::keypressed(const keycode _code)
	{
		key_state* state = keys.at(_code);
		if (state == nullptr)
			return false;

		return state->held;
	}
}
