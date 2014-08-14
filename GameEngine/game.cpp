#include <GLM\gtc\matrix_transform.hpp>
#include "game.h"
#include "renderEngine.h"
#include "transform.h"
#include "common.h"
#include "input.h"
Game::Game()
{
	Vertex data[] = {Vertex(vec3(-1.0,-1.0, 1.0)),
					Vertex(vec3(1.0,-1.0,1.0)),
					Vertex(vec3(-1.0,1.0,1.0)),
					Vertex(vec3(1.0,1.0,1.0)),
					Vertex(vec3(-1.0, -1.0, -1.0)),
					Vertex(vec3(1.0, -1.0, -1.0)),
					Vertex(vec3(-1.0, 1.0, -1.0)),
					Vertex(vec3(1.0, 1.0, -1.0))};

	int indices[] = { 0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1 };


	m_mesh.AddVertices(data, ARRAY_SIZE(data), indices, ARRAY_SIZE(indices));

	m_shader.AddVertexShaderFromFile("vertexshader.glsl");
	m_shader.AddFragmentShaderFromFile("fragmentshader.glsl");
	m_shader.LinkProgram();
	m_shader.AddUniform("MVPMatrix");
	printf("%f %f %f", m_camera.GetUp().x, m_camera.GetUp().y, m_camera.GetUp().z);
	//m_transform.SetTranslate(vec3(0.0f, 0.0f, -2.0f));
	//m_transform.SetScale(vec3(1.3f, 1.3f, 1.3f));
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
	m_transform.SetTranslation(vec3(0, 0, -5.0));
	m_transform.SetRotation((float)(sinTemp*180.0), vec3(0.0, 1.0, 0.0));
	
}

void Game::Render()
{
	m_shader.Bind();
	m_shader.SetUniform("MVPMatrix", m_transform.GetModelViewProjectionMatrix(m_camera));
	 
	RenderEngine::ClearScreen();
	m_mesh.Draw();
}
