#include "input.h"

#include <GLFW/glfw3.h>

namespace CycloneEngine
{
	map<keycode, input::key_state> input::keys;

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
		if (keys.count(code) == 0)
		{
			keys.insert({code, key_state(code)});
		}

		key_state* key = &keys.at(code);

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
		for (auto& state : keys)
		{
			if (state.second.up && state.second.held)
				state.second.up = false;

			if(state.second.down)
				state.second.down = false;
		}
	}

	bool input::keyup(const keycode _code)
	{
		if (keys.count(_code) == 0)
			return false;

		key_state state = keys.at(_code);
		return state.up;
	}

	bool input::keydown(const keycode _code)
	{
		if (keys.count(_code) == 0)
			return false;

		key_state state = keys.at(_code);
		return state.down;
	}

	bool input::keypressed(const keycode _code)
	{
		if (keys.count(_code) == 0)
			return false;

		key_state state = keys.at(_code);
		return state.held;
	}
}
