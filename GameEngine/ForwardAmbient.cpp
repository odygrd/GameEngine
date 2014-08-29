#include "forwardambient.h"
#include "../rendering/texture.h"
#include "../rendering/camera.h"
#include "../rendering/renderEngine.h"
#include "../rendering/material.h"
#include "../components/lighting.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

ForwardAmbient::ForwardAmbient()
{
	AddVertexShaderFromFile("../data/shaders/multipass/multipass-ambient.vs.glsl");
	AddFragmentShaderFromFile("../data/shaders/multipass/multipass-ambient.fs.glsl");
	LinkProgram();
}

ForwardAmbient::~ForwardAmbient()
{
}

void ForwardAmbient::UpdateUniforms(const mat4& modelmatrix, const Material& material)
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
	SetUniform("ambientColor", GetRenderEngine()->GetAmbientLight()->GetColor());
	SetUniform("sampler", 0);
}