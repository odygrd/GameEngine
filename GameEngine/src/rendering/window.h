#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
class Window
{
public:
	Window(int width, int height, const std::string& title);
	~Window();

	void Update();

	inline bool GetIsCloseRequest() { return m_closeRequest; };
	void SetFullScreen(bool value);

	static void error_callback(int error, const char* description);
	//static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	inline  int GetWidth() { return m_width; }
	inline  int GetHeight() { return m_height; }
	inline  const std::string& GetTitle() { return m_title; }
private:
	int m_width;
	int m_height;
	bool m_closeRequest;
	std::string m_title;
	GLFWwindow* m_window;

};

#endif