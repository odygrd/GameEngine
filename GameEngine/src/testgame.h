#ifndef TESTGAME_H
#define TESTGAME_H

#include "rendering\mesh.h"
#include "meshes\cube.h"
#include "meshes\plane.h"
#include "rendering\shader.h"
#include "rendering\camera.h"
#include "rendering\texture.h"
#include "rendering\material.h"
#include "rendering\lighting.h"
#include "core\common.h"
#include "core\input.h"
#include "core\transform.h"
#include "core\game.h"
#include "rendering\renderEngine.h"

class TestGame : public Game
{
public:
	TestGame();
	virtual ~TestGame();

	virtual void Init(const Window& window);
	//virtual void ProcessInput(const Input& input, float delta);
	virtual void ProcessInput(){};
	virtual void Update(float delta);
	virtual void Render(RenderEngine* renderEngine);
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
	SpotLight* m_sLights;
};

#endif