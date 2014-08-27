#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <GL\glew.h>
#include "..\core\gameobject.h"
#include "shader.h"
#include "camera.h"
#include "lighting.h"


class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();
	void Render(GameObject* gameobject);

	void ClearScreen();
	inline const char* GetOpenGLVersion() { return (char*)glGetString(GL_VERSION); }
	inline const char* GetRenderer() { return (char*)glGetString(GL_RENDERER); }

	inline void Input() { mainCamera->Input(); }

	inline Camera* GetCamera(){ return mainCamera; }

private:
	Camera* mainCamera;
	Shader* m_shader;

	PointLight* m_pLights;
	SpotLight* m_sLights;
};

#endif