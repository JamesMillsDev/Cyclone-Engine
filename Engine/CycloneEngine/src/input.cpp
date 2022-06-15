#include "Input.h"

#include <GLFW/glfw3.h>

namespace CycloneEngine
{
	Input* input = nullptr;
	
	Input::KeyState::KeyState(const Keycode _code) : key(_code), held(false), up(false), down(false)
	{
	}

	Input::Input()
	{
		m_lastKeys = new int[GLFW_KEY_LAST + 1];
		m_currentKeys = new int[GLFW_KEY_LAST + 1];
	
		m_mouseX = 0;
		m_mouseY = 0;
		m_mouseScroll = 0;
	}

	void Input::Update()
	{
		m_pressedCharacters.clear();

		const auto window = glfwGetCurrentContext();

		m_pressedKeys.clear();

		// update keys
		for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i) {

			m_lastKeys[i] = m_currentKeys[i];

			if ((m_currentKeys[i] = glfwGetKey(window, i)) == GLFW_PRESS)
				m_pressedKeys.push_back(m_currentKeys[i]);
		}

		// update mouse
		for (int i = 0; i < 8 ; ++i) {
			m_lastButtons[i] = m_currentButtons[i];
			m_currentButtons[i] = glfwGetMouseButton(window, i);
		}

		// update old mouse position
		m_oldMouseX = m_mouseX;
		m_oldMouseY = m_mouseY;
	}

	bool Input::KeyUp(const Keycode _code) const
	{
		return m_currentKeys[(int)_code] == GLFW_RELEASE;
	}

	bool Input::KeyDown(const Keycode _code) const
	{
		return m_lastKeys[(int)_code] == GLFW_PRESS;
	}

	bool Input::KeyPressed(const Keycode _code) const
	{
		return m_currentKeys[(int)_code] == GLFW_PRESS;
	}
}
