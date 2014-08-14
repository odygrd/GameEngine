#ifndef WINDOW_H
#define WINDOW_H
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <string>
class Window
{
public:
	static void Create(int width, int height, const std::string& title);
	static void Update();
	static void Dispose();

	static bool IsCloseRequested();
	static void SetFullScreen(bool value);

	static void error_callback(int error, const char* description);
	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	inline static int GetWidth() { return m_width; }
	inline static int GetHeight() { return m_height; }
	inline static const std::string& GetTitle() { return m_title; }
private:
	static int m_width;
	static int m_height;
	static std::string m_title;
	static GLFWwindow* m_window;
};

#endif