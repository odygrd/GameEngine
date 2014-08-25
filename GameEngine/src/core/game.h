#ifndef GAME_H
#define GAME_H

#include "../rendering/mesh.h"
#include "../meshes\cube.h"
#include "../rendering/shader.h"
#include "../rendering/camera.h"
#include "../rendering/texture.h"
#include "../rendering/material.h"
#include "transform.h"

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
	Shader* m_shader;
	Transform m_transform;
	Camera m_camera;
	Texture* m_texture;
	Material m_material;
};

#endif