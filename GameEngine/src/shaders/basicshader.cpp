#include "basicshhader.h"
#include "../rendering/texture.h"
#include "../core/common.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

BasicShader::BasicShader()
{
	AddVertexShaderFromFile("../data/shaders/vertexshader.glsl");
	AddFragmentShaderFromFile("../data/shaders/fragmentshader.glsl");
	LinkProgram();
}

BasicShader::~BasicShader()
{
}

void BasicShader::UpdateUniforms(const mat4& MVPMatrix, Material material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.GetTexture() != NULL)
		material.GetTexture()->Bind(0);
	else
	{
		WHITE.Bind(0);
	}

	SetUniform("MVPMatrix", MVPMatrix);
	SetUniform("color", material.GetColor());
}