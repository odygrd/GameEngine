#include "renderEngine.h"
#include "..\shaders\phongshader.h"

RenderEngine::RenderEngine()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);

	mainCamera = new Camera(FOV, WIDTH / HEIGHT, ZNEAR, ZFAR);
	m_shader = PhongShader::GetInstance();

	PhongShader::SetAmbientLight(AmbientLight(0.1f));
	//PhongShader::SetDirectionalLight(DirectionalLight(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 0.8f), 0.4f));

	//myvector.push_back(PointLight(vec3(-8, -2.0, 0), vec3(0.8f, 0.2f, 0.0f), 10.0f, 0.8f));
	//myvector.push_back(PointLight(vec3(8, -2.0, 0), vec3(0.0f, 0.5f, 0.9f), 10.0f, 0.8f));
	//myvector.push_back(PointLight(vec3(6, -1.5, 4.0), vec3(0.0f, 0.9f, 0.2f), 10.0f, 0.85f));
	//PhongShader::SetPointLights(&myvector[0], myvector.size());

	m_pLights = new PointLight[3];
	m_pLights[0] = PointLight(vec3(-8, -2.0, 0), vec3(0.8f, 0.2f, 0.0f), 10.0f, 0.8f);
	m_pLights[1] = PointLight(vec3(8, -2.0, 0), vec3(0.0f, 0.5f, 0.9f), 10.0f, 0.8f);
	m_pLights[2] = PointLight(vec3(6, -1.5, 4.0), vec3(0.0f, 0.9f, 0.2f), 10.0f, 0.85f);
	PhongShader::SetPointLights(m_pLights, 3);

	m_sLights = new SpotLight[1];
	m_sLights[0] = SpotLight(vec3(0.0f, 3.0, 0.0f), vec3(0.0f, 5.0f, 0.0f), vec3(1.0f, 0.8f, 0.3f), 0.9f, 0.85f, 20.0f);
	PhongShader::SetSpotLights(m_sLights, 1);
}

void RenderEngine::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderEngine::Render(GameObject* gameobject)
{
	ClearScreen();
	
	m_shader->SetRenderEngine(this);
	gameobject->RenderAll(m_shader,this);
}

RenderEngine::~RenderEngine()
{
	delete[] m_pLights;
	delete[] m_sLights;
	delete mainCamera;
	//delete m_shader;
}