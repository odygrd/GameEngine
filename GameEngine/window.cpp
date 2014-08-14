#include <cstdio>

#include "window.h"
#include "main.h"
#include "input.h"

int Window::m_width;
int Window::m_height;
std::string Window::m_title;
GLFWwindow* Window::m_window;

void Window::Create(int width, int height, const std::string& title)
{
	Window::m_width = width;
	Window::m_height = height;
	Window::m_title = title;

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
		Window::Dispose();
		exit(EXIT_FAILURE);
	}
	//glfwSetWindowSize(m_window, width, height);
	glfwMakeContextCurrent(m_window);
	glfwSetKeyCallback(m_window, Input::KeyCallback);
	glfwSetMouseButtonCallback(m_window, Input::MouseButtonCallback);
	glfwSetCursorPosCallback(m_window, Input::CursorPosCallback);
	glfwSetScrollCallback(m_window, Input::CursorScrollCallback);

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
		Window::Dispose();
		exit(EXIT_SUCCESS);
	}

	glfwSwapBuffers(m_window);
}

void Window::Dispose()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::IsCloseRequested()
{
	return false;
}

void Window::SetFullScreen(bool value)
{

}

void Window::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}



