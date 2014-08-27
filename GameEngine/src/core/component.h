#ifndef COMPONENT_H
#define COMPONENT_H
#include "..\core\gameobject.h"
class Shader;
class RenderEngine;
class Core;
class Transform;

class GameComponent
{
public:
	virtual ~GameComponent() {}

	virtual void Input(float delta) {}
	virtual void Update(float delta) {}
	virtual void Render(Shader* shader, RenderEngine* renderingEngine) {}

	virtual void AddToEngine(Core* engine) { }

	inline void SetParent(GameObject* parent) { m_parent = parent; }
	inline Transform& GetTransform() { return m_parent->GetTransform(); }
	inline const Transform& GetTransform() const { return m_parent->GetTransform(); }

private:
	GameObject* m_parent;
};

#endif