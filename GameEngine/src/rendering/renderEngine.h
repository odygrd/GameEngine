#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <GL\glew.h>
#include <string>

class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();

	static void InitGraphics();
	static void ClearScreen();
	inline static const char* GetOpenGLVersion() { return (char*)glGetString(GL_VERSION); }
	inline static const char* GetRenderer() { return (char*)glGetString(GL_RENDERER); }
};

#endif