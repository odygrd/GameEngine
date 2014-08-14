#ifndef MESH_H
#define MESH_H
#include "GL\glew.h"
#include "common.h"

class Vertex
{
public:
	Vertex(vec3 position, vec2 texCoord = vec2(0, 0), vec3 normal = vec3(0, 0, 0)) : m_position(position), m_texCoord(texCoord), m_normal(normal) 
	{}

	inline const vec3& GetPosition() { return m_position; }
	inline const vec2& GetTexCoord() { return m_texCoord; }
	inline const vec3& GetNormal() { return m_normal; }
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

	void AddVertices(Vertex* vertices, unsigned int vertSize, int* indices, unsigned int indexSize, bool calcNormals = true);
	void Draw();
private:
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_ibo;
	unsigned int m_size;
};

#endif
