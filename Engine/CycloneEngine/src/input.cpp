#include "Input.h"

#include <GLFW/glfw3.h>

namespace CycloneEngine
{
	map<Keycode, Input::KeyState> Input::keys;

	Input::KeyState::KeyState(const Keycode _code) : key(_code), held(false), up(false), down(false)
	{
	}

	void Input::init(GLFWwindow* _window)
	{
		glfwSetKeyCallback(_window, keyCallback);
	}

	void Input::keyCallback(GLFWwindow* _window, int _key, int _scancode, const int _action, int _mods)
	{
		Keycode code = static_cast<Keycode>(_key);
		if (keys.count(code) == 0)
		{
			keys.insert({code, KeyState(code)});
		}

		KeyState* key = &keys.at(code);

		if (_action == GLFW_PRESS)
		{
			key->down = true;
			key->held = false;
		}
		else if(_action == GLFW_REPEAT)
		{
			key->down = false;
			key->held = true;
		}
		else if(_action == GLFW_RELEASE)
		{
			key->up = true;
			key->held = false;
		}
	}

	void Input::update()
	{
		for (auto& state : keys)
		{
			if (state.second.up && state.second.held)
				state.second.up = false;

			if(state.second.down)
				state.second.down = false;
		}
	}

	bool Input::keyup(const Keycode _code)
	{
		if (keys.count(_code) == 0)
			return false;

		KeyState state = keys.at(_code);
		return state.up;
	}

	bool Input::keydown(const Keycode _code)
	{
		if (keys.count(_code) == 0)
			return false;

		KeyState state = keys.at(_code);
		return state.down;
	}

	bool Input::keypressed(const Keycode _code)
	{
		if (keys.count(_code) == 0)
			return false;

		KeyState state = keys.at(_code);
		return state.held;
	}
}
