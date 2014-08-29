#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;

out vec3 vertexPosition;
out vec2 vertexTexCoord;
out vec3 vertexNormal;

uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{	
	vertexTexCoord = vTexCoord;
	vertexNormal = normalize(NormalMatrix * vNormal);
	vertexPosition = vec3(ModelMatrix * vec4(vPosition,1.0));

	gl_Position = MVP * vec4(vPosition,1.0);
}
