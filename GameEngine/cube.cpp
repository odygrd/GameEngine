#include "cube.h"

Cube::Cube()
{
	float side = 1.0f;
	float side2 = side / 2.0f;

	Vertex data[] = {
		// Front
		Vertex(vec3(-side2, -side2, side2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
		Vertex(vec3(side2, -side2, side2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
		Vertex(vec3(side2, side2, side2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)),
		Vertex(vec3(-side2, side2, side2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, 1.0f)),
		// Right
		Vertex(vec3(side2, -side2, side2), vec2(0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
		Vertex(vec3(side2, -side2, -side2), vec2(1.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f)),
		Vertex(vec3(side2, side2, -side2), vec2(1.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
		Vertex(vec3(side2, side2, side2), vec2(0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f)),
		// Back
		Vertex(vec3(-side2, -side2, -side2), vec2(0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
		Vertex(vec3(-side2, side2, -side2), vec2(1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
		Vertex(vec3(side2, side2, -side2), vec2(1.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)),
		Vertex(vec3(side2, -side2, -side2), vec2(0.0f, 1.0f), vec3(0.0f, 0.0f, -1.0f)),
		// Left
		Vertex(vec3(-side2, -side2, side2), vec2(0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(vec3(-side2, side2, side2), vec2(1.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(vec3(-side2, side2, -side2), vec2(1.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)),
		Vertex(vec3(-side2, -side2, -side2), vec2(0.0f, 1.0f), vec3(-1.0f, 0.0f, 0.0f)),
		// Bottom
		Vertex(vec3(-side2, -side2, side2), vec2(0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
		Vertex(vec3(-side2, -side2, -side2), vec2(1.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
		Vertex(vec3(side2, -side2, -side2), vec2(1.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),
		Vertex(vec3(side2, -side2, side2), vec2(0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),
		// Top
		Vertex(vec3(-side2, side2, side2), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(side2, side2, side2), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(side2, side2, -side2), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(-side2, side2, -side2), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f))
	};

	int indices[] = {
		0, 1, 2, 0, 2, 3,
		4, 5, 6, 4, 6, 7,
		8, 9, 10, 8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	AddVertices(data, ARRAY_SIZE(data), indices, ARRAY_SIZE(indices), false);
}

Cube::~Cube()
{

}