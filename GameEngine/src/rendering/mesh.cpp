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
	glDeleteVertexArrays(1, &m_vao);
}

void Mesh::AddVertices(Vertex* vertices, unsigned int vertSize, int* indices, unsigned int indexSize, bool calcNormals)
{
	m_size = indexSize;

	if (calcNormals)
		this->CalcNormals(vertices, vertSize, indices, indexSize);

	//Bind
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(Vertex), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(int), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(vec3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(vec3) + sizeof(vec2)));
	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER,0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
}

void Mesh::Draw()
{
	glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glDrawElements(GL_TRIANGLES, m_size, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
#include <iostream>
void Mesh::CalcNormals(Vertex* vertices, int vertSize, int* indices, int indexSize)
{
	for (int i = 0; i < indexSize; i += 3)
	{
		int i0 = indices[i];
		int i1 = indices[i + 1];
		int i2 = indices[i + 2];

		vec3 v1 = vertices[i1].GetPosition() - vertices[i0].GetPosition();
		vec3 v2 = vertices[i2].GetPosition() - vertices[i0].GetPosition();

		vec3 normal = glm::normalize(glm::cross(v1, v2)); 

		vertices[i0].SetNormal(vertices[i0].GetNormal() + normal);
		vertices[i1].SetNormal(vertices[i1].GetNormal() + normal);
		vertices[i2].SetNormal(vertices[i2].GetNormal() + normal);
	}

	for (int i = 0; i < vertSize; i++)
		vertices[i].SetNormal(glm::normalize(vertices[i].GetNormal()));
}