#include <GLM\gtc\matrix_transform.hpp>
#include "game.h"
#include "renderEngine.h"
#include "transform.h"
#include "common.h"
#include "input.h"
#include "texture.h"
#include "basicshhader.h"
#include "phongphader.h"

Game::Game()
{
	m_texture = new Texture("./data/textures/wooden.jpg");
	m_material = Material(m_texture);

	m_shader = PhongShader::GetInstance();
	PhongShader::SetAmbientLight(vec3(0.2f, 0.2f, 0.2f));
	PhongShader::SetDirectionalLight(DirectionalLight(vec3(1.0f, 1.0f, 1.0f), vec3(0.8f, 1.0f, 0.8f), 0.9f));

	m_transform.SetTranslation(vec3(0.0f, 0.0f, -2.0f));
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
	
	m_transform.SetRotation((float)(sinTemp*180.0), vec3(0.0, 1.0, 0.0));
	
}

void Game::Render()
{
	m_shader->Bind();
	m_shader->UpdateUniforms(m_transform.GetModelViewMatrix(m_camera), m_transform.GetProjectionMatrix(), m_material);
	RenderEngine::ClearScreen();
	m_cube.Draw();
}
