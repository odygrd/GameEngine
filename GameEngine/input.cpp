#include <cstdio>
#include "input.h"

bool Input::m_keyInputs[NUM_KEYS];
bool Input::m_pressKeys[NUM_KEYS];
bool Input::m_releaseKeys[NUM_KEYS];

bool Input::m_mouseInputs[NUM_MOUSEBUTTONS];
bool Input::m_pressMouse[NUM_MOUSEBUTTONS];
bool Input::m_releaseMouse[NUM_MOUSEBUTTONS];

vec2 Input::m_mousePos;
vec2 Input::m_scrollOffset;

void Input::Update()
{
	glfwPollEvents();
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	for (int i = 0; i < NUM_KEYS; i++)
	{
		m_pressKeys[i] = false;
		m_releaseKeys[i] = false;
	}

	if (action == GLFW_PRESS)
	{
		m_keyInputs[key] = true;
		m_pressKeys[key] = true;
	}

	if (action == GLFW_RELEASE)
	{
		m_keyInputs[key] = false;
		m_releaseKeys[key] = true;
	}

}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	for (int i = 0; i < NUM_MOUSEBUTTONS; i++)
	{
		m_pressMouse[i] = false;
		m_releaseMouse[i] = false;
	}

	if (action == GLFW_PRESS)
	{
		m_mouseInputs[button] = true;
		m_pressMouse[button] = true;
	}

	if (action == GLFW_RELEASE)
	{
		m_mouseInputs[button] = false;
		m_releaseMouse[button] = true;
	}
}

void Input::CursorPosCallback(GLFWwindow* window, double posX, double posY)
{
	m_mousePos.x = (float)posX;
	m_mousePos.y = (float)posY;
	
}

void Input::CursorScrollCallback(GLFWwindow* window, double offsetX, double offsetY)
{
	m_scrollOffset.x = (float)offsetX;
	m_scrollOffset.y = (float)offsetY;
}

void Input::SetCursorVisibility(GLFWwindow* window, bool visible)
{
	visible ? glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL) : glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

