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
#include "..\rendering\renderEngine.h"

class Game
{
public:
	Game();
	virtual ~Game();

	virtual void Init(const Window& window);
	//virtual void ProcessInput(const Input& input, float delta);
	virtual void ProcessInput(){};
	virtual void Update(float delta);
	virtual void Render(RenderEngine* renderEngine);

private:
	Game(Game& game){}
	void operator=(Game& game){}
};

#endif