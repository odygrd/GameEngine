#ifndef GAME_H
#define GAME_H
#include "gameobject.h"

class Game
{
public:
	Game(){};
	virtual ~Game(){};

	virtual void Init(){};
	void ProcessInput(float delta){ m_root.InputAll(delta); }
	void Update(float delta){ m_root.UpdateAll(delta); }
	/// void Render(RenderEngine* renderEngine){ m_root.RenderAll(m_shader, renderEngine); };
	inline GameObject& GetRootObject() { return m_root; }
private:
	Game(Game& game){}
	void operator=(Game& game){}

	GameObject m_root;
};

#endif