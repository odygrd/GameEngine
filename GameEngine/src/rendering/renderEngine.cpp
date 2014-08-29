#include "renderEngine.h"
#include "../Shaders/forwardambient.h"
#include "../Shaders/ForwardDirectional.h"
#include "../Shaders/ForwardPoint.h"
#include "../shaders/ForwardSpot.h"
#include "../components/lighting.h"
#include "../core/gameobject.h"
#include "camera.h"

RenderEngine::RenderEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);

	mainCamera = new Camera(FOV, WIDTH / HEIGHT, ZNEAR, ZFAR);
	m_forwardAmbient = ForwardAmbient::GetInstance();
	m_ambientLight = new AmbientLight(Color(0.1f,0.1f,0.1f));

}

void RenderEngine::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::Render(GameObject* gameobject)
{
	ClearScreen();
	m_lights.clear();

	gameobject->AddToRenderingEngine(this);

	m_ambientLight->GetShader()->SetRenderEngine(this);
	gameobject->RenderAll(m_ambientLight->GetShader(), this);


	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(false);
	glDepthFunc(GL_EQUAL);

	for (auto light : m_lights)
	{
		light->GetShader()->SetRenderEngine(this);
		m_activeLight = light;
		gameobject->RenderAll(light->GetShader(), this);
	}

	glDepthFunc(GL_LESS);
	glDepthMask(true);
	glDisable(GL_BLEND);

	
}

RenderEngine::~RenderEngine()
{
	//delete[] m_pLights;
	//delete[] m_sLights;
	delete mainCamera;
}


void RenderEngine::Input() { mainCamera->Input(); }