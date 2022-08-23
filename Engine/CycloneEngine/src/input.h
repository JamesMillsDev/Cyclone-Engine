#ifndef CYCLONE_INPUT
#define CYCLONE_INPUT

#include <vector>
#include <functional>
#include <map>

using std::vector;
using std::function;
using std::map;

namespace CycloneEditor
{
    class Window;
}

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

namespace CycloneEngine
{
    enum class Keycode
    {
        Unknown = -1,
        Spacebar = 32,
        Apostrophe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,
        Num0 = 48,
        Num1 = 49,
        Num2 = 50,
        Num3 = 51,
        Num4 = 52,
        Num5 = 53,
        Num6 = 54,
        Num7 = 55,
        Num8 = 56,
        Num9 = 57,
        Semicolon = 59,
        Equal = 61,
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LeftBracket = 91,
        Backslash = 92,
        RightBracket = 93,
        GraveAccent = 96,
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        Numpad0 = 320,
        Numpad1 = 321,
        Numpad2 = 322,
        Numpad3 = 323,
        Numpad4 = 324,
        Numpad5 = 325,
        Numpad6 = 326,
        Numpad7 = 327,
        Numpad8 = 328,
        Numpad9 = 329,
        NumpadDecimal = 330,
        NumpadDivide = 331,
        NumpadMultiply = 332,
        NumpadSubtract = 333,
        NumpadAdd = 334,
        NumpadEnter = 335,
        NumpadEqual = 336,
        LeftShift = 340,
        LeftControl = 341,
        LeftAlt = 342,
        LeftSuper = 343,
        RightShift = 344,
        RightControl = 345,
        RightAlt = 346,
        RightSuper = 347,
        Menu = 348
    };

    class Input
    {
    public:
        static Input* GetInstance() { return m_instance; }

        // query the keyboard state
        bool IsKeyDown(Keycode _inputKeyId);
        bool IsKeyUp(Keycode _inputKeyId);

        // returns true if the key was pressed / released this frame
        bool WasKeyPressed(Keycode _inputKeyId);
        bool WasKeyReleased(Keycode _inputKeyId);

        // query the mouse button state
        bool IsMouseButtonDown(int _inputMouseId);
        bool IsMouseButtonUp(int _inputMouseId);

        // returns true if the button was pressed / released this frame
        bool WasMouseButtonPressed(int _inputMouseId);
        bool WasMouseButtonReleased(int _inputMouseId);

        // query the mouse position
        int GetMouseX();
        int GetMouseY();
        void GetMousePos(int* _x, int* _y);

        // query mouse movement
        int GetMouseDeltaX();
        int GetMouseDeltaY();
        void GetMouseDelta(int* _x, int* _y);

        // query how far the mouse wheel has been moved 
        double GetMouseScroll();

        typedef function<void(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)> KeyCallback;
        typedef function<void(GLFWwindow* _window, unsigned int _character)> CharCallback;
        typedef function<void(GLFWwindow* _window, int _button, int _action, int _mods)> MouseButtonCallback;
        typedef function<void(GLFWwindow* _window, double _xOffset, double _yOffset)> MouseScrollCallback;
        typedef function<void(GLFWwindow* _window, double _x, double _y)> MouseMoveCallback;

        void AttachKeyObserver(const KeyCallback& _callback) { m_instance->m_keyCallbacks.push_back(_callback); }
        void AttachCharObserver(const CharCallback& _callback) { m_instance->m_charCallbacks.push_back(_callback); }
        void AttachMouseButtonObserver(const MouseButtonCallback& _callback) { m_instance->m_mouseButtonCallbacks.push_back(_callback); }
        void AttachMouseMoveObserver(const MouseMoveCallback& _callback) { m_instance->m_mouseMoveCallbacks.push_back(_callback); }
        void AttachMouseScrollObserver(const MouseScrollCallback& _callback) { m_instance->m_mouseScrollCallbacks.push_back(_callback); }

    private:
        static void CreateInstance(void* _window);
        static void DestroyInstance();
        void ClearStatus(void* _window);

        Input(void* _window);
        ~Input();
        Input(const Input&) = delete;

        static Input* m_instance;

        vector<int> m_pressedKeys;
        vector<unsigned int> m_pressedCharacters;

        int m_mouseX;
        int m_mouseY;
        int m_oldMouseX;
        int m_oldMouseY;
        double m_mouseScroll;

        bool m_firstMouseMove; // flag for first mouse input after start or mouse entering window

        void OnMouseMove(int _newXPos, int _newYPos);

        vector<KeyCallback> m_keyCallbacks;
        vector<CharCallback> m_charCallbacks;
        vector<MouseMoveCallback> m_mouseMoveCallbacks;
        vector<MouseButtonCallback> m_mouseButtonCallbacks;
        vector<MouseScrollCallback> m_mouseScrollCallbacks;

        // used to track down/up/released/pressed
        int *m_lastKeys, *m_currentKeys;
        int m_lastButtons[8], m_currentButtons[8];

        friend class CycloneEditor::Window;
    };
}

#endif //!CYCLONE_INPUT
