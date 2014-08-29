#include "ForwardDirectional.h"
#include "../rendering/texture.h"
#include <GLM/gtc/matrix_inverse.inl>
#include "../rendering/camera.h"
#include "../components/lighting.h"
#include "../rendering/renderEngine.h"
#include "../rendering/material.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

ForwardDirectional::ForwardDirectional()
{
	AddVertexShaderFromFile("../data/shaders/multipass/multipass-directional.vs.glsl");
	AddFragmentShaderFromFile("../data/shaders/multipass/multipass-directional.fs.glsl");
	LinkProgram();
}

ForwardDirectional::~ForwardDirectional()
{
}

void ForwardDirectional::UpdateUniforms(const mat4& modelMatrix, const Material& material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.GetTexture() != NULL)
		material.GetTexture()->Bind(0);
	else
	{
		WHITE.Bind(0);
	}
	mat4 MVP = GetRenderEngine()->GetCamera()->GetProjectionMatrix() * GetRenderEngine()->GetCamera()->GetViewMatrix() * modelMatrix;

	SetUniform("MVP", MVP);
	SetUniform("ModelMatrix", modelMatrix);
	SetUniform("NormalMatrix", glm::inverseTranspose(mat3(modelMatrix)));

	SetUniform("directionalLight.direction", static_cast<DirectionalLight*>(GetRenderEngine()->GetActiveLight())->GetDirection());
	SetUniform("directionalLight.base.color", static_cast<DirectionalLight*>(GetRenderEngine()->GetActiveLight())->GetColor());
	SetUniform("directionalLight.base.intensity", static_cast<DirectionalLight*>(GetRenderEngine()->GetActiveLight())->GetIntensity());

	SetUniform("specularIntensity", material.GetSpecularIntensity());
	SetUniform("specularPower", material.GetSpecularPower());
	SetUniform("eyePosition", GetRenderEngine()->GetCamera()->GetPosition());
}