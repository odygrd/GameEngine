#ifndef MESH_H
#define MESH_H
#include "GL\glew.h"
#include "../core/common.h"

class Vertex
{
public:
	Vertex(vec3 position, vec2 texCoord = vec2(0, 0), vec3 normal = vec3(0, 0, 0)) : m_position(position), m_texCoord(texCoord), m_normal(normal) 
	{}

	inline const vec3& GetPosition() const { return m_position; }
	inline const vec2& GetTexCoord() const { return m_texCoord; }
	inline const vec3& GetNormal() const { return m_normal; }
	inline void SetPosition(const vec3& position){ m_position = position; }
	inline void SetNormal(const vec3& normal){ m_normal = normal; }
	inline void SetTexCoord(const vec2& texcoord){ m_texCoord = texcoord; }
private:
	vec3 m_position;
	vec2 m_texCoord;
	vec3 m_normal;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void AddVertices(Vertex* vertices, unsigned int vertSize, int* indices, unsigned int indexSize, bool calcNormals = false);
	virtual void Draw();
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	unsigned int m_size;

	void CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize);
};

#endif
