#include <GLM\gtc\matrix_transform.hpp>
#include "game.h"
#include "renderEngine.h"
#include "transform.h"
#include "common.h"
#include "input.h"
#include "texture.h"

Game::Game()
{
	//Vertex data[] = { Vertex(vec3(-1.0, -1.0, 1.0), vec2(0.0f, 1.0f)),
	//				Vertex(vec3(1.0, -1.0, 1.0), vec2(1.0f, 1.0f)),
	//				Vertex(vec3(-1.0, 1.0, 1.0), vec2(0.0f, 1.0f)),
	//				Vertex(vec3(1.0, 1.0, 1.0), vec2(1.0f, 1.0f)),
	//				Vertex(vec3(-1.0, -1.0, -1.0), vec2(0.0f,0.0f)),
	//				Vertex(vec3(1.0, -1.0, -1.0), vec2(1.0f, 0.0f)),
	//				Vertex(vec3(-1.0, 1.0, -1.0), vec2(0.0f, 0.0f)),
	//				Vertex(vec3(1.0, 1.0, -1.0), vec2(0.0f, 0.0f)) };

	int indices[] = { 0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1 };


	Vertex data[] = {
		//  X     Y     Z       U     V
		// bottom
		Vertex(vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(1.0f, -1.0f, 1.0f), vec2(1.0f, 1.0f)),
		Vertex(vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f)),

		// top
		Vertex(vec3(-1.0f, 1.0f, -1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(-1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(-1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),

		// front
		Vertex(vec3(-1.0f, -1.0f, 1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(-1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
		Vertex(vec3(1.0f, -1.0f, 1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(-1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),

		// back
		Vertex(vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(-1.0f, 1.0f, -1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(-1.0f, 1.0f, -1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(1.0f, 1.0f, -1.0f), vec2(1.0f, 1.0f)),

		// left
		Vertex(vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(-1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(-1.0f, -1.0f, -1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(-1.0f, -1.0f, 1.0f), vec2(0.0f, 1.0f)),
		Vertex(vec3(-1.0f, 1.0f, 1.0f), vec2(1.0f, 1.0f)),
		Vertex(vec3(-1.0f, 1.0f, -1.0f), vec2(1.0f, 0.0f)),

		// right
		Vertex(vec3(1.0f, -1.0f, 1.0f), vec2(1.0f, 1.0f)),
		Vertex(vec3(1.0f, -1.0f, -1.0f), vec2(1.0f, 0.0f)),
		Vertex(vec3(1.0f, 1.0f, -1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(1.0f, -1.0f, 1.0f), vec2(1.0f, 1.0f)),
		Vertex(vec3(1.0f, 1.0f, -1.0f), vec2(0.0f, 0.0f)),
		Vertex(vec3(1.0f, 1.0f, 1.0f), vec2(0.0f, 1.0f))
	};


	m_mesh.AddVertices(data, ARRAY_SIZE(data), indices, ARRAY_SIZE(indices));

	m_shader.AddVertexShaderFromFile("vertexshader.glsl");
	m_shader.AddFragmentShaderFromFile("fragmentshader.glsl");
	m_shader.LinkProgram();
	m_shader.AddUniform("MVPMatrix");
	m_texture = new Texture("./data/textures/wooden.jpg");
	m_transform.SetTranslation(vec3(0.0f, 0.0f, -2.0f));
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
	m_texture->Bind(0);
	RenderEngine::ClearScreen();
	m_mesh.Draw();
}
