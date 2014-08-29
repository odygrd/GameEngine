#ifndef TESTGAME_H
#define TESTGAME_H

#include "../core/gameobject.h"
#include "../core/game.h"

class Material;
class Texture;
class Cube;
class Plane;
class MeshRenderer;
class Mesh;
class DirectionalLight;
class PointLight;
class SpotLight;

class TestGame : public Game
{
public:
	TestGame(){};
	virtual ~TestGame();

	virtual void Init();
private:
	Cube* m_cube;
	Plane* m_plane;
	Transform m_transform;
	Texture* m_texture[2];
	Material* m_material[2];

	Mesh* m_mesh;
	Mesh* m_mesh1;
	GameObject go;
	GameObject go1;
	MeshRenderer* m_meshrender;
	MeshRenderer* m_meshrender1;
	//std::vector<PointLight> myvector;

	GameObject dirlight;
	DirectionalLight* dlight;
	DirectionalLight* dlight2;
	PointLight* pLight;
	SpotLight* sLight;
};

#endif