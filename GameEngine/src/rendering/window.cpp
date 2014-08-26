#include <cstdio>

#include "window.h"
#include "../core/input.h"


Window::Window(int width, int height, const std::string& title) : m_closeRequest(false), m_width(width), m_height(height), m_title(title)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	(SAMPLES > 0) ? glfwWindowHint(GLFW_SAMPLES, SAMPLES) : glfwWindowHint(GLFW_SAMPLES, 0);
	(WINDOW_RESIZABLE) ? glfwWindowHint(GLFW_RESIZABLE, GL_TRUE) : glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (FULLSCREEN)
	{
		m_window = glfwCreateWindow(width, height, title.c_str(), glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	}

	if (!m_window)
	{
		printf("Failed to initialize window\n");
		m_closeRequest = true;
	}
	//glfwSetWindowSize(m_window, width, height);
	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, Input::KeyCallback);
	glfwSetMouseButtonCallback(m_window, Input::MouseButtonCallback);
	glfwSetCursorPosCallback(m_window, Input::CursorPosCallback);
	glfwSetScrollCallback(m_window, Input::CursorScrollCallback);
	
	Input::SetWindow(m_window);
	// Initialize GLEW
	glewExperimental = GL_TRUE; //Turn glewExperimental on to avoid problem fetching function pointers...
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize GLEW");
		exit(EXIT_FAILURE);
	}
}
void Window::Update()
{
	if (glfwWindowShouldClose(m_window))
	{
		m_closeRequest = true;
	}

	glfwSwapBuffers(m_window);
}

void Window::SetFullScreen(bool value)
{

}

void Window::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

