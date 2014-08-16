#include "basicshhader.h"
#include "texture.h"
#include "common.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

BasicShader::BasicShader()
{
	AddVertexShaderFromFile("vertexshader.glsl");
	AddFragmentShaderFromFile("fragmentshader.glsl");
	LinkProgram();

	AddUniform("MVPMatrix");
	AddUniform("color");
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