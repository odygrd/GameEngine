#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "../components/component.h"
#include "../rendering/shader.h"
class Mesh;
class Material;
class Shader;

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