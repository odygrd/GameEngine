#include "basicshader.h"
#include "../rendering/texture.h"
#include "../rendering/camera.h"
#include "../rendering/renderEngine.h"
#include "../rendering/material.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

BasicShader::BasicShader()
{
	AddVertexShaderFromFile("../data/shaders/simplevertex.glsl");
	AddFragmentShaderFromFile("../data/shaders/simplefragment.glsl");
	LinkProgram();
}

BasicShader::~BasicShader()
{
}

void BasicShader::UpdateUniforms(const mat4& modelmatrix, const Material& material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.GetTexture() != NULL)
		material.GetTexture()->Bind(0);
	else
	{
		WHITE.Bind(0);
	}
	mat4 MVP = GetRenderEngine()->GetCamera()->GetProjectionMatrix() * GetRenderEngine()->GetCamera()->GetViewMatrix() * modelmatrix;
	SetUniform("MVP", MVP);
	SetUniform("ambientIntensity", material.GetColor());
}