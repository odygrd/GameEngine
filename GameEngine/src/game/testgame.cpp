#include "../core/core.h"
#include "testgame.h"
#include "../Meshes/cube.h"
#include "../Meshes/plane.h"
#include "../rendering/texture.h"
#include "../rendering/material.h"
#include "../components/meshrenderer.h"
#include "../rendering/window.h"
#include "../components/lighting.h"
#include "../rendering/renderEngine.h"

#include <VLD\vld.h>

void TestGame::Init() {
	m_texture[0] = new Texture("./data/textures/wooden.jpg");
	m_material[0] = new Material(m_texture[0], vec3(1.0, 1.0, 1.0), 2.0f, 32.0f);

	m_texture[1] = new Texture("./data/textures/checkerboard2.jpg");
	m_material[1] = new Material(m_texture[1], vec3(1.0, 1.0, 1.0), 2.0f, 32.0f);

	m_cube = new Cube();
	m_plane = new Plane();
	m_mesh = new Mesh();
	m_mesh1 = new Mesh();

	m_meshrender = new MeshRenderer(m_cube, m_material[0]);
	m_meshrender1 = new MeshRenderer(m_plane, m_material[1]);
	go.AddComponent(m_meshrender);
	go1.AddComponent(m_meshrender1);
	//go.GetTransform().SetTranslation(vec3(0.0f, -10.0f, 0.0f));
	//go.GetTransform().SetRotation(90.0f, vec3(1.0f, 0.0f, 0.0f));

	dlight = new DirectionalLight(Color(1.0f, 0.0f, 0.0f), vec3(2.0f, 1.0f, 1.0f), 0.4f);
	dlight2 = new DirectionalLight(Color(0.0f, 1.0f, 1.0f), vec3(-2.0f, 1.0f, 1.0f), 0.4f);
	dirlight.AddComponent(dlight);
	dirlight.AddComponent(dlight2);

	pLight = new PointLight(Color(1.0f, 0.2f, 0.0f), vec3(-6.0f, -2.0f, 2.0f), 1.0f, 10.0f);
	dirlight.AddComponent(pLight);

	sLight = new SpotLight(Color(0.7f, 0.0f, 0.5f), vec3(0.0f, 3.0f, 0.0f), vec3(0.0f, 5.0f, 0.0), 0.8f, 0.9f, 30.0f,Attenuation(1,0,0));
	dirlight.AddComponent(sLight);

	GetRootObject().AddChild(&go);
	GetRootObject().AddChild(&go1);
	GetRootObject().AddChild(&dirlight);

}

TestGame::~TestGame()
{
	//delete m_material[0];
	//delete m_material[1];
	delete m_texture[0];
	delete m_texture[1];

	delete m_mesh;
	delete m_mesh1;
}

int main()
{
	
	Window window(1280, 720, "3D Game Engine");
	RenderEngine renderer;

	//window.SetFullScreen(true);
	TestGame game;
	Core engine(&window, &renderer, &game,FRAME_CAP);
	engine.Start();
	return 0;
}
