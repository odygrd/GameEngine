#include <cstdio>
#include <Windows.h>

#include "core.h"

#include "common.h"
#include "input.h"

double Time::m_delta;

Core::Core(Window* window, RenderEngine* renderEngine, Game* game, double framerate) :
	m_isRunning(false), 
	m_frameTime(1.0 / framerate),
	m_window(window),
	m_renderEngine(renderEngine),
	m_game(game)
{
	Time::SetDelta(m_frameTime);
	m_game->Init(*m_window);
};

void Core::Start()
{
	if (m_isRunning)
	{
		return;
	}
	m_isRunning = true;

	printf("OpenGL Version: %s\n", m_renderEngine->GetOpenGLVersion());
	printf("Renderer: %s\n", m_renderEngine->GetRenderer());

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

		while (unprocessedTime > m_frameTime)
		{
			if (m_window->GetIsCloseRequest())
			{
				Stop();
			}

			Input::Update();
			m_game->ProcessInput();
			m_game->Update((float)m_frameTime);
			render = true;
			unprocessedTime -= m_frameTime;
		}

		if (render || IGNORE_FRAME_CAP)
		{
			m_game->Render(m_renderEngine);
			m_window->Update();
			frames++;
		}
		else
		{
			Sleep(1);
		}
	}
}


void Core::Stop()
{
	m_isRunning = false;
}
