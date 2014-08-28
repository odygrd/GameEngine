#include "ForwardDirectional.h"
#include "../rendering/texture.h"
#include <GLM/gtc/matrix_inverse.inl>

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

ForwardDirectional::ForwardDirectional()
{
	AddVertexShaderFromFile("../data/shaders/forward.directional.vs.glsl");
	AddFragmentShaderFromFile("../data/shaders/forward.directional.fs.glsl");
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

	SetUniform("directionalLight.direction", GetRenderEngine()->GetDirectionalLight().GetDirection());
	SetUniform("directionalLight.base.color", GetRenderEngine()->GetDirectionalLight().GetColor());
	SetUniform("directionalLight.base.intensity", GetRenderEngine()->GetDirectionalLight().GetIntensity());

	SetUniform("specularIntensity", material.GetSpecularIntensity());
	SetUniform("specularPower", material.GetSpecularPower());
	SetUniform("eyePosition", GetRenderEngine()->GetCamera()->GetPosition());
}