#include "mesh.h"

Mesh::Mesh()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	m_size = 0;
}


Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vbo);
}

void Mesh::AddVertices(Vertex* vertices, unsigned int vertSize, int* indices, unsigned int indexSize, bool calcNormals)
{
	m_size = indexSize;
	//Bind
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec3));
	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
}

void Mesh::Draw()
{
	glBindVertexArray(m_vao);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	//glDrawElements(GL_TRIANGLE_STRIP, m_size, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}