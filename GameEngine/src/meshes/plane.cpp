#include "plane.h"
#include "../core/common.h"

Plane::Plane()
{
	float side = 2.0f;
	float side2 = 1.0f;

	Vertex data[] = {
		Vertex(vec3(-10.0f, -3.0f, 10.0f), vec2(0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(10.0f, -3.0f, 10.0f), vec2(1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(10.0f, -3.0f, -10.0f), vec2(1.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f)),
		Vertex(vec3(-10.0f, -3.0f, -10.0f), vec2(0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f))

	};

	int indices[] = {
		0, 1, 2, 0, 2, 3
	};

	AddVertices(data, ARRAY_SIZE(data), indices, ARRAY_SIZE(indices), false);
}

Plane::~Plane()
{

}