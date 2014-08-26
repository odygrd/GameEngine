#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <GL\glew.h>

class RenderEngine
{
public:
	RenderEngine();

	void ClearScreen();
	inline const char* GetOpenGLVersion() { return (char*)glGetString(GL_VERSION); }
	inline const char* GetRenderer() { return (char*)glGetString(GL_RENDERER); }
};

#endif