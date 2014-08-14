#include <cstdio>
#include <Windows.h>

#include "main.h"
#include "window.h"
#include "common.h"
#include "input.h"
#include "game.h"
#include "renderEngine.h"

double Time::m_delta = 1 / FRAME_CAP;

Main::Main()
{
	printf("OpenGL Version: %s\n", RenderEngine::GetOpenGLVersion());
	printf("Renderer: %s\n", RenderEngine::GetRenderer());
	RenderEngine::InitGraphics();
	m_isRunning = false;
}

Main::~Main()
{

}

void Main::Start()
{
	if (m_isRunning)
	{
		return;
	}
	m_isRunning = true;
	Run();
}

void Main::Stop()
{
	if (!m_isRunning)
	{
		return;
	}
	m_isRunning = false;
}

void Main::Run()
{
	const double frameTime = 1 / FRAME_CAP; //time for each frame
	double lastTime = glfwGetTime();
	double unprocessedTime = 0; 
	double frameCounter = 0;
	int frames = 0;

	while (m_isRunning)
	{
		bool render = false;
		double startTime = glfwGetTime();
		double passedTime = startTime - lastTime; // Compute time difference between current and last frame

		lastTime = startTime;

		unprocessedTime += passedTime;
		frameCounter += passedTime;

		//if 1 second passed print and reset
		if (frameCounter >= 1.0f)
		{
			//printf("%i\n", frames);
			frames = 0;
			frameCounter = 0;
		}

		while (unprocessedTime > frameTime)
		{
			render = true;

			Input::Update();
			m_game.Input();
			m_game.Update();
			unprocessedTime -= frameTime;
		}

		if (render || IGNORE_FRAME_CAP)
		{
			m_game.Render();
			Window::Update();
			frames++;
		}
		else
		{
			Sleep(1);
		}
	}
}

int main()
{
	Window::Create((int)WIDTH, (int)HEIGHT, "3D Engine");
	Main main;
	main.Start();

	return 0;
}