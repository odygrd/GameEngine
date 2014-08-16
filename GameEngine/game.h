#ifndef GAME_H
#define GAME_H
#include "mesh.h"
#include "shader.h"
#include "transform.h"
#include "camera.h"
#include "texture.h"
#include "material.h"

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
	Shader* m_shader;
	Transform m_transform;
	Camera m_camera;
	Texture* m_texture;
	Material m_material;
};

#endif