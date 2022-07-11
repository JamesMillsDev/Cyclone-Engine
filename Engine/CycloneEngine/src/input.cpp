#include "Input.h"

#include <GLFW/glfw3.h>

namespace CycloneEngine
{
    Input* Input::m_instance = nullptr;

    bool Input::IsKeyDown(Keycode _inputKeyId)
    {
        return m_instance->m_currentKeys[(int)_inputKeyId] == GLFW_PRESS;
    }

    bool Input::IsKeyUp(Keycode _inputKeyId)
    {
        return m_instance->m_currentKeys[(int)_inputKeyId] == GLFW_RELEASE;
    }

    bool Input::WasKeyPressed(Keycode _inputKeyId)
    {
        return m_instance->m_currentKeys[(int)_inputKeyId] == GLFW_PRESS &&
            m_instance->m_lastKeys[(int)_inputKeyId] == GLFW_RELEASE;
    }

    bool Input::WasKeyReleased(Keycode _inputKeyId)
    {
        return m_instance->m_currentKeys[(int)_inputKeyId] == GLFW_RELEASE &&
            m_instance->m_lastKeys[(int)_inputKeyId] == GLFW_PRESS;
    }

    bool Input::IsMouseButtonDown(const int _inputMouseId)
    {
        return m_instance->m_currentButtons[_inputMouseId] == GLFW_PRESS;
    }

    bool Input::IsMouseButtonUp(const int _inputMouseId)
    {
        return m_instance->m_currentButtons[_inputMouseId] == GLFW_RELEASE;
    }

    bool Input::WasMouseButtonPressed(const int _inputMouseId)
    {
        return m_instance->m_currentButtons[_inputMouseId] == GLFW_PRESS &&
            m_instance->m_lastButtons[_inputMouseId] == GLFW_RELEASE;
    }

    bool Input::WasMouseButtonReleased(const int _inputMouseId)
    {
        return m_instance->m_currentButtons[_inputMouseId] == GLFW_RELEASE &&
            m_instance->m_lastButtons[_inputMouseId] == GLFW_PRESS;
    }

    int Input::GetMouseX()
    {
        return m_instance->m_mouseX;
    }

    int Input::GetMouseY()
    {
        return m_instance->m_mouseY;
    }

    void Input::GetMousePos(int* _x, int* _y)
    {
        if (_x != nullptr)
            *_x = m_instance->m_mouseX;

        if (_y != nullptr)
            *_y = m_instance->m_mouseY;
    }

    int Input::GetMouseDeltaX()
    {
        return m_instance->m_mouseX - m_instance->m_oldMouseX;
    }

    int Input::GetMouseDeltaY()
    {
        return m_instance->m_mouseY - m_instance->m_oldMouseY;
    }

    void Input::GetMouseDelta(int* _x, int* _y)
    {
        if (_x != nullptr)
            *_x = m_instance->m_mouseX - m_instance->m_oldMouseX;
        
        if (_y != nullptr)
            *_y = m_instance->m_mouseY - m_instance->m_oldMouseY;
    }

    double Input::GetMouseScroll()
    {
        return m_instance->m_mouseScroll;
    }

    void Input::CreateInstance(void* _window)
    {
        if (m_instance != nullptr)
            return;

        m_instance = new Input(_window);
    }

    void Input::DestroyInstance()
    {
        if (m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

    void Input::ClearStatus(void* _window)
    {
        auto window = (GLFWwindow*)_window;

        m_pressedCharacters.clear();

        m_pressedKeys.clear();

        // update keys
        for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
        {
            m_lastKeys[i] = m_currentKeys[i];

            if ((m_currentKeys[i] = glfwGetKey(window, i)) == GLFW_PRESS)
                m_pressedKeys.push_back(m_currentKeys[i]);
        }

        // update mouse
        for (int i = 0; i < 8; ++i)
        {
            m_instance->m_lastButtons[i] = m_instance->m_currentButtons[i];
            m_instance->m_currentButtons[i] = glfwGetMouseButton(window, i);
        }

        // update old mouse position
        m_instance->m_oldMouseX = m_instance->m_mouseX;
        m_instance->m_oldMouseY = m_instance->m_mouseY;
    }

    Input::Input(void* _window)
    {
        auto window = (GLFWwindow*)_window;

        // track current/previous key and mouse button states
        m_lastKeys = new int[GLFW_KEY_LAST + 1];
        m_currentKeys = new int[GLFW_KEY_LAST + 1];

        for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
            m_lastKeys[i] = m_currentKeys[i] = glfwGetKey(window, i);

        for (int i = 0; i < 8; ++i)
            m_lastButtons[i] = m_currentButtons[i] = glfwGetMouseButton(window, i);

        // set up callbacks
        auto keyPressCallback = [](GLFWwindow* _window, const int _key, const int _scancode, const int _action,
                                   const int _mods)
        {
            for (auto& f : m_instance->m_keyCallbacks)
                f(_window, _key, _scancode, _action, _mods);
        };

        auto characterInputCallback = [](GLFWwindow* _window, const unsigned int _character)
        {
            m_instance->m_pressedCharacters.push_back(_character);

            for (auto& f : m_instance->m_charCallbacks)
                f(_window, _character);
        };

        auto mouseMoveCallback = [](GLFWwindow* _window, const double _x, const double _y)
        {
            int w = 0, h = 0;
            glfwGetWindowSize(_window, &w, &h);

            m_instance->OnMouseMove((int)_x, h - (int)_y);

            for (auto& f : m_instance->m_mouseMoveCallbacks)
                f(_window, _x, h - _y);
        };

        auto mouseInputCallback = [](GLFWwindow* _window, const int _button, const int _action, const int _mods)
        {
            for (auto& f : m_instance->m_mouseButtonCallbacks)
                f(_window, _button, _action, _mods);
        };

        auto mouseScrollCallback = [](GLFWwindow* _window, const double _xOffset, double _yOffset)
        {
            m_instance->m_mouseScroll += _yOffset;

            for (auto& f : m_instance->m_mouseScrollCallbacks)
                f(_window, _xOffset, _yOffset);
        };

        auto mouseEnterCallback = [](GLFWwindow* _window, int _entered)
        {
            // Set flag to prevent large mouse delta on entering screen
            m_instance->m_firstMouseMove = true;
        };

        glfwSetKeyCallback(window, keyPressCallback);
        glfwSetCharCallback(window, characterInputCallback);
        glfwSetMouseButtonCallback(window, mouseInputCallback);
        glfwSetCursorPosCallback(window, mouseMoveCallback);
        glfwSetScrollCallback(window, mouseScrollCallback);
        glfwSetCursorEnterCallback(window, mouseEnterCallback);

        m_mouseX = 0;
        m_mouseY = 0;
        m_mouseScroll = 0;
        m_oldMouseX = 0;
        m_oldMouseY = 0;
        m_firstMouseMove = false;
    }

    Input::~Input()
    {
        delete[] m_lastKeys;
        delete[] m_currentKeys;
    }

    void Input::OnMouseMove(const int _newXPos, const int _newYPos)
    {
        m_mouseX = _newXPos;
        m_mouseY = _newYPos;
        if (m_firstMouseMove)
        {
            // On first move after startup/entering window reset old mouse position
            m_oldMouseX = _newXPos;
            m_oldMouseY = _newYPos;
            m_firstMouseMove = false;
        }
    }
}
