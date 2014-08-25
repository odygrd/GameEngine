#include "renderEngine.h"

RenderEngine::RenderEngine()
{
}


RenderEngine::~RenderEngine()
{
}

void RenderEngine::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::InitGraphics()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
	
}