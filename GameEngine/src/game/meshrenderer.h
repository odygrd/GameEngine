#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "..\core\gameobject.h"
#include "..\rendering\mesh.h"
#include "..\rendering\material.h"
#include "..\rendering\shader.h"
#include "..\core\component.h"

class MeshRenderer : public GameComponent
{
public:
	MeshRenderer(Mesh* mesh, Material* material)
	{
		m_mesh = mesh;
		m_material = material;
	}

	virtual ~MeshRenderer()
	{
		if (m_mesh) delete m_mesh;
		if (m_material) delete m_material;
	}

	virtual void Input(float delta) {}
	virtual void Update(float delta) {}
	virtual void Render(Shader* shader, RenderEngine* renderingEngine)
	{
		shader->Bind();
		shader->UpdateUniforms(GetTransform().GetTransformMatrix(), m_material[0]);
		m_mesh->Draw();
	}
protected:
private:
	Mesh* m_mesh;
	Material* m_material;
};

#endif 