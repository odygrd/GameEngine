#ifndef CORE_H
#define CORE_H
#include "..\rendering\window.h"
#include "..\rendering\renderEngine.h"
#include "game.h"

class Core
{
public:
	Core(Window* window, RenderEngine* renderEngine, Game* game, double framerate);

	void Start();
	void Stop();

	void SetIsRunning(bool isRunning){ m_isRunning = isRunning; }

private:
	bool m_isRunning;
	double m_frameTime;
	Window* m_window;
	RenderEngine* m_renderEngine;
	Game* m_game;
};

#endif