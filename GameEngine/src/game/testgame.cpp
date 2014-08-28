#include "..\core\core.h"
#include "testgame.h"
#include "../Meshes/cube.h"
#include "../Meshes/plane.h"
#include <VLD\vld.h>

void TestGame::Init() {
	m_texture[0] = new Texture("./data/textures/wooden.jpg");
	m_material[0] = new Material(m_texture[0], vec3(1.0, 1.0, 1.0), 2.0f, 32.0f);

	m_texture[1] = new Texture("./data/textures/checkerboard2.jpg");
	m_material[1] = new Material(m_texture[1], vec3(1.0, 1.0, 1.0), 2.0f, 32.0f);

	Vertex data[] = {
		Vertex(vec3(-10.0f, -3.0f, 10.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(10.0f, -3.0f, 10.0f), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(10.0f, -3.0f, -10.0f), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(-10.0f, -3.0f, -10.0f), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f))

	};

	int indices[] = {
		0, 1, 2, 0, 2, 3
	};

	m_cube = new Cube();
	m_plane = new Plane();
	m_mesh = new Mesh();
	m_mesh1 = new Mesh();
	//m_mesh->AddVertices(data, ARRAY_SIZE(data), indices, ARRAY_SIZE(indices), false);
	m_meshrender = new MeshRenderer(m_cube, m_material[0]);
	m_meshrender1 = new MeshRenderer(m_plane, m_material[1]);
	go.AddComponent(m_meshrender);
	go1.AddComponent(m_meshrender1);
	go.AddChild(&go1);
	//go.GetTransform().SetTranslation(vec3(0.0f, -10.0f, 0.0f));
	//go.GetTransform().SetRotation(90.0f, vec3(1.0f, 0.0f, 0.0f));
	GetRootObject().AddChild(&go);

}

TestGame::~TestGame()
{
	//delete m_material[0];
	//delete m_material[1];
	delete m_texture[0];
	delete m_texture[1];

	delete m_mesh;
	delete m_mesh1;
	//delete m_cube;
	//delete m_plane;

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
