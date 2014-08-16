#ifndef INPUT_H
#define INPUT_H
#include <GLFW\glfw3.h>
#include "common.h"

class Input
{
public:
	static void Update();
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void CursorPosCallback(GLFWwindow* window, double posX, double posY);
	static void CursorScrollCallback(GLFWwindow* window, double offsetX, double posY);

	inline static bool GetKey(int keyCode) { return m_keyInputs[keyCode]; }
	inline static bool GetKeyDown(int keyCode) { return m_pressKeys[keyCode]; }
	inline static bool GetKeyUp(int keyCode) { return m_releaseKeys[keyCode]; }

	inline static bool GetMouse(const int button) { return m_mouseInputs[button]; }
	inline static bool GetMouseDown(const int button){ return m_pressMouse[button]; }
	inline static bool GetMouseUp(const int button){ return m_releaseMouse[button]; }

	static const vec2& GetCursorPosition();
	inline static const vec2& GetScrollOffset() { return m_scrollOffset; }

	inline static void SetWindow(GLFWwindow* window) { m_window = window; }
	static void SetCursorVisibility(bool visible);
	static void SetCursorPosition(vec2 position);

private:
	static vec2 m_mousePos;
	static vec2 m_scrollOffset;
	static GLFWwindow* m_window;

	static bool m_keyInputs[NUM_KEYS];
	static bool m_pressKeys[NUM_KEYS];
	static bool m_releaseKeys[NUM_KEYS];

	static bool m_mouseInputs[NUM_MOUSEBUTTONS];
	static bool m_pressMouse[NUM_MOUSEBUTTONS];
	static bool m_releaseMouse[NUM_MOUSEBUTTONS];
};

#endif