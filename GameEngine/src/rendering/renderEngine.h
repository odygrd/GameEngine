#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <GL\glew.h>
#include "..\core\gameobject.h"
#include "shader.h"
#include "camera.h"
#include "lighting.h"
#include <memory>

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

	inline const vec3& GetAmbientLight(){ return m_ambientLight; }
	inline const DirectionalLight& GetDirectionalLight(){ return m_directionalLight; }
private:
	Camera* mainCamera;
	Shader* m_forwardAmbient;
	Shader* m_forwardDirectional;

	PointLight* m_pLights;
	SpotLight* m_sLights;

	vec3 m_ambientLight;
	DirectionalLight m_directionalLight;
	DirectionalLight m_directionalLight2;
};

#endif