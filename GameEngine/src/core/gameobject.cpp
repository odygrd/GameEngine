#include "gameobject.h"
#include "../components/component.h"

GameObject* GameObject::AddChild(GameObject* child)
{
	m_children.push_back(child);
	//child->GetTransform().SetParent(&m_transform);
//	child->SetEngine(m_coreEngine);
	return this;
}

GameObject* GameObject::AddComponent(GameComponent* component)
{
	m_components.push_back(component);
	component->SetParent(this);
	return this;
}

void GameObject::InputAll(float delta)
{
	Input(delta);

	for (auto child : m_children)
		child->InputAll(delta);
}

void GameObject::UpdateAll(float delta)
{
	Update(delta);

	for (auto child : m_children)
		child->UpdateAll(delta);
}

void GameObject::RenderAll(Shader* shader, RenderEngine* renderingEngine)
{
	Render(shader, renderingEngine);

	for (auto child : m_children)
		child->RenderAll(shader, renderingEngine);
}

void GameObject::AddToRenderingEngine(RenderEngine* renderEngine)
{
	for (auto componnent : m_components)
	{
		componnent->AddToRenderingEngine(renderEngine);
	}
	for (auto child : m_children)
	{

		child->AddToRenderingEngine(renderEngine);
	}

}

void GameObject::Input(float delta)
{
	//m_transform.Update();

	for (auto componnent : m_components)
		componnent->Input(delta);
}

void GameObject::Update(float delta)
{
	for (auto componnent : m_components)
		componnent->Update(delta);
}

void GameObject::Render(Shader* shader, RenderEngine* renderingEngine)
{
	for (auto componnent : m_components)
		componnent->Render(shader, renderingEngine);
}

void GameObject::SetEngine(Core* engine)
{
	if (m_coreEngine != engine)
	{
		m_coreEngine = engine;

		for (auto componnent : m_components)
			componnent->AddToEngine(engine);

		for (auto child : m_children)
			child->SetEngine(engine);
	}
}

std::vector<GameObject*> GameObject::GetAllAttached()
{
	std::vector<GameObject*> result;

	for (auto child : m_children)
	{
		std::vector<GameObject*> childObjects = child->GetAllAttached();
		result.insert(result.end(), childObjects.begin(), childObjects.end());
	}

	result.push_back(this);
	return result;
}

GameObject::~GameObject()
{
	for (auto componnent : m_components)
		if (componnent)
			delete componnent;

	//for (auto child : m_children)
	//	if (child)
	//		delete child;
}