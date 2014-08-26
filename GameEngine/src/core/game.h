#ifndef GAME_H
#define GAME_H

#include "../rendering/mesh.h"
#include "../meshes/cube.h"
#include "../meshes/plane.h"
#include "../rendering/shader.h"
#include "../rendering/camera.h"
#include "../rendering/texture.h"
#include "../rendering/material.h"
#include "transform.h"
#include "../rendering/lighting.h"

class Game
{
public:
	Game();
	~Game();

	void Input();
	void Update();
	void Render();
private:
	Mesh m_mesh;
	Cube m_cube;
	Plane m_plane;
	Shader* m_shader;
	Transform m_transform;
	Camera m_camera;
	Texture* m_texture[2];
	Material* m_material[2];
	PointLight* m_pLights;
};

#endif