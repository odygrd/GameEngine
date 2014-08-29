#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include "transform.h"

class Core;
class GameComponent;
class Shader;
class RenderEngine;

class GameObject
{
public:
	GameObject() { m_coreEngine = nullptr; }
	virtual ~GameObject();

	GameObject* AddChild(GameObject* child);
	GameObject* AddComponent(GameComponent* component);

	void InputAll(float delta);
	void UpdateAll(float delta);
	void RenderAll(Shader* shader, RenderEngine* renderingEngine);

	std::vector<GameObject*> GetAllAttached();

	inline Transform& GetTransform() { return m_transform; }
	void SetEngine(Core* engine);
	void AddToRenderingEngine(RenderEngine* renderEngine);
protected:
private:
	void Input(float delta);
	void Update(float delta);
	void Render(Shader* shader, RenderEngine* renderingEngine);

	std::vector<GameObject*> m_children;
	std::vector<GameComponent*> m_components;
	Transform m_transform;
	Core* m_coreEngine;
};




#endif
