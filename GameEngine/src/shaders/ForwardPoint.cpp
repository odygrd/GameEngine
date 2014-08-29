#include "ForwardPoint.h"
#include "../rendering/texture.h"
#include <GLM/gtc/matrix_inverse.inl>
#include "../rendering/camera.h"
#include "../rendering/renderEngine.h"
#include "../components/lighting.h"
#include "../rendering/material.h"
#include <iostream>


static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

ForwardPoint::ForwardPoint()
{
	AddVertexShaderFromFile("../data/shaders/multipass/multipass-point.vs.glsl");
	AddFragmentShaderFromFile("../data/shaders/multipass/multipass-point.fs.glsl");
	LinkProgram();
}

ForwardPoint::~ForwardPoint()
{
}

void ForwardPoint::UpdateUniforms(const mat4& modelMatrix, const Material& material)
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

	SetUniform("pointlight.base.color", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetColor());
	SetUniform("pointlight.base.intensity", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetIntensity());
	SetUniform("pointlight.atten.constant", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetConstantAttenuation());
	SetUniform("pointlight.atten.linear", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetLinearAttenuation());
	SetUniform("pointlight.atten.exponent", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetExponentAttenuation());
	SetUniform("pointlight.position", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetPosition());
	SetUniform("pointlight.range", static_cast<PointLight*>(GetRenderEngine()->GetActiveLight())->GetRange());

}