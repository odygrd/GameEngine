#include "../rendering/renderEngine.h"
#include "../rendering/texture.h"
#include "../shaders/basicshhader.h"
#include "../shaders/phongphader.h"
#include "game.h"
#include "transform.h"
#include "common.h"
#include "input.h"

#include <GLM\gtc\matrix_transform.hpp>

Game::Game()
{
	m_texture[0] = new Texture("./data/textures/wooden.jpg");
	m_material[0] = new Material(m_texture[0],vec3(1.0,1.0,1.0), 2.0f, 32.0f);

	m_texture[1] = new Texture("./data/textures/checkerboard2.jpg");
	m_material[1] = new Material(m_texture[1], vec3(1.0, 1.0, 1.0), 2.0f, 32.0f);

	m_shader = PhongShader::GetInstance();

	PhongShader::SetAmbientLight(AmbientLight(0.1f));
	//PhongShader::SetDirectionalLight(DirectionalLight(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 0.8f), 0.4f));

	m_pLights = new PointLight[3];
	m_pLights[0] = PointLight(vec3(-8, -2.0, 0), vec3(0.8f, 0.2f, 0.0f), 10.0f ,0.8f);
	m_pLights[1] =  PointLight(vec3(8, -2.0, 0), vec3(0.0f, 0.5f, 0.9f), 10.0f,  0.8f);
	m_pLights[2] = PointLight(vec3(6, -1.5, 4.0), vec3(0.0f, 0.9f, 0.2f), 10.0f, 0.85f);
	PhongShader::SetPointLights(m_pLights, 3);

	m_sLights = new SpotLight[1];
	m_sLights[0] = SpotLight(vec3(0.0f, 1.0, 5.0f),vec3(0.0f,1.0f,2.0f),vec3(1.0f,0.8f,0.3f),20.9f,0.85f,20.0f);
	PhongShader::SetSpotLights(m_sLights, 1);
	//m_transform.SetTranslation(vec3(0.0f, 0.0f, -2.0f));
	//m_transform.SetScale(vec3(3.3f, 3.3f, 3.3f));
	//m_transform.SetRotation(40, vec3(0.0, 0.0, 1.0));
}

Game::~Game()
{
}

void Game::Input()
{

}

float temp = 0;
void Game::Update()
{
	temp += (float)(1 / FRAME_CAP);
	float sinTemp = (float)sin(temp);
	m_camera.Input();
	
	//m_transform.SetRotation((float)30.0f, vec3(0.0, 1.0, 0.0));

	//m_pLights[0].SetPosition(vec3(-1, -2, -2.0f * (float)(sin(temp) + 1.0 / 2.0)));
	//m_pLights[1].SetPosition(vec3(1, -2, -1.0f * (float)(cos(temp) + 1.0 / 2.0) + 1.0));
}

void Game::Render()
{
	RenderEngine::ClearScreen();
	m_shader->Bind();
	m_shader->UpdateUniforms(m_transform.GetTransformMatrix(), m_transform.GetModelViewProjectionMatrix(m_camera), m_camera.GetPosition(), *m_material[0]);
	
	m_cube.Draw();

	m_shader->UpdateUniforms(m_transform.GetTransformMatrix(), m_transform.GetModelViewProjectionMatrix(m_camera), m_camera.GetPosition(), *m_material[1]);
	m_plane.Draw();
}
