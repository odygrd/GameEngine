#pragma once
#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <GL/glew.h>
#include "../core/common.h"
#include <vector>

class GameObject;
class Shader;
class Camera;
class AmbientLight;
class BaseLight;

class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();
	void Render(GameObject* gameobject);

	void ClearScreen();
	inline const char* GetOpenGLVersion() { return reinterpret_cast<char*> (const_cast<unsigned char*>(glGetString(GL_VERSION))); }
	inline const char* GetRenderer() { return reinterpret_cast<char*> (const_cast<unsigned char*>(glGetString(GL_RENDERER))); }

	void Input();

	inline Camera* GetCamera(){ return mainCamera; }

	inline const AmbientLight* GetAmbientLight(){ return m_ambientLight; }

	inline void AddLight(BaseLight* light){ m_lights.push_back(light); }
	inline BaseLight* GetActiveLight() { return m_activeLight; }
private:
	Camera* mainCamera;
	Shader* m_forwardAmbient;

	AmbientLight* m_ambientLight;

	std::vector<BaseLight*> m_lights;
	BaseLight* m_activeLight;
};

#endif