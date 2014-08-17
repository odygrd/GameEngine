#version 330
uniform mat4 MVPMatrix;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 out_texCoord;

void main()
{
	out_texCoord = texCoord;
    gl_Position = MVPMatrix * vec4(position, 1.0);
}
