#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 out_texCoord;

uniform mat4 MVP;

void main()
{
	out_texCoord = texCoord;
    gl_Position = MVP * vec4(position, 1.0);
}
