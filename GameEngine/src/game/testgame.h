#ifndef TESTGAME_H
#define TESTGAME_H

#include "..\core\transform.h"
#include "..\core\gameobject.h"
#include "meshrenderer.h"
#include "..\core\game.h"

class Material;
class Texture;

class TestGame : public Game
{
public:
	TestGame(){};
	virtual ~TestGame();

	virtual void Init();
private:
	
	Transform m_transform;
	Texture* m_texture[2];
	Material* m_material[2];

	Mesh* m_mesh;
	GameObject go;
	MeshRenderer* m_meshrender;
	//std::vector<PointLight> myvector;
};

#endif