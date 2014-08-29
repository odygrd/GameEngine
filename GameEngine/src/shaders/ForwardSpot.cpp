#include "ForwardSpot.h"
#include "../rendering/texture.h"
#include <GLM/gtc/matrix_inverse.inl>
#include "../rendering/camera.h"
#include "../components/lighting.h"
#include "../rendering/renderEngine.h"
#include "../rendering/material.h"
#include <iostream>


static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

ForwardSpot::ForwardSpot()
{
	AddVertexShaderFromFile("../data/shaders/multipass/multipass-spotlight.vs.glsl");
	AddFragmentShaderFromFile("../data/shaders/multipass/multipass-spotlight.fs.glsl");
	LinkProgram();
}

ForwardSpot::~ForwardSpot()
{
}

void ForwardSpot::UpdateUniforms(const mat4& modelMatrix, const Material& material)
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

	SetUniform("specularIntensity", material.GetSpecularIntensity());
	SetUniform("specularPower", material.GetSpecularPower());
	SetUniform("eyePosition", GetRenderEngine()->GetCamera()->GetPosition());

	SetUniform("spotlight.pLight.base.color",static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetColor());
	SetUniform("spotlight.pLight.base.intensity", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetIntensity());
	SetUniform("spotlight.pLight.atten.constant", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetConstantAttenuation());
	SetUniform("spotlight.pLight.atten.linear", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetLinearAttenuation());
	SetUniform("spotlight.pLight.atten.exponent", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetExponentAttenuation());
	SetUniform("spotlight.pLight.position", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetPosition());
	SetUniform("spotlight.pLight.range", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetRange());
	SetUniform("spotlight.direction", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetDirection());
	SetUniform("spotlight.cutoff", static_cast<SpotLight*>(GetRenderEngine()->GetActiveLight())->GetCutOff());

}