#include "phongphader.h"
#include <GLM\gtc\matrix_inverse.hpp>

#include "../rendering/texture.h"
#include "../core/common.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };

AmbientLight PhongShader::m_ambientLight;
DirectionalLight PhongShader::m_directionalLight; 
PointLight* PhongShader::m_pointLights = NULL;
SpotLight* PhongShader::m_spotLights = NULL;

int PhongShader::m_numPointLights = 0;
int PhongShader::m_numSpotLights = 0;

PhongShader::PhongShader()
{
	AddVertexShaderFromFile("../data/shaders/phongvertex.glsl");
	AddFragmentShaderFromFile("../data/shaders/phongfragment.glsl");
	LinkProgram();
}

PhongShader::~PhongShader()
{
}

void PhongShader::UpdateUniforms(const mat4& modelViewMatrix, const mat4& projectionMatrix, const vec3& cameraPosition,const Material& material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.GetTexture() != NULL)
		material.GetTexture()->Bind(0);
	else
	{
		WHITE.Bind(0);
	}

	SetUniform("MVP", projectionMatrix);
	SetUniform("ModelViewMatrix", modelViewMatrix);
	SetUniform("NormalMatrix", glm::inverseTranspose(mat3(modelViewMatrix))); 
	SetUniform("basecolor", material.GetColor());
	SetUniform("ambientLight.color", m_ambientLight.GetColor());
	SetUniform("ambientLight.intensity", m_ambientLight.GetIntensity());
	SetUniform("directionalLight.direction", m_directionalLight.GetDirection());
	SetUniform("directionalLight.base.color", m_directionalLight.GetColor());
	SetUniform("directionalLight.base.intensity", m_directionalLight.GetIntensity());
	SetUniform("specularIntensity", material.GetSpecularIntensity());
	SetUniform("specularPower", material.GetSpecularPower());
	SetUniform("eyePosition", cameraPosition);

	for (int i = 0; i < m_numPointLights; i++)
	{
		std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		SetUniform(pointLightName + ".base.color", m_pointLights[i].GetColor());
		SetUniform(pointLightName + ".base.intensity", m_pointLights[i].GetIntensity());
		SetUniform(pointLightName + ".atten.constant", m_pointLights[i].GetConstantAttenuation());
		SetUniform(pointLightName + ".atten.linear", m_pointLights[i].GetLinearAttenuation());
		SetUniform(pointLightName + ".atten.exponent", m_pointLights[i].GetExponentAttenuation());
		SetUniform(pointLightName + ".position", m_pointLights[i].GetPosition());
		SetUniform(pointLightName + ".range", m_pointLights[i].GetRange());
	}

	for (int i = 0; i < m_numSpotLights; i++)
	{
		std::string pointLightName = "spotLights[" + std::to_string(i) + "]";

		SetUniform(pointLightName + ".pLight.base.color", m_spotLights[i].GetColor());
		SetUniform(pointLightName + ".pLight.base.intensity", m_spotLights[i].GetIntensity());
		SetUniform(pointLightName + ".pLight.atten.constant", m_spotLights[i].GetConstantAttenuation());
		SetUniform(pointLightName + ".pLight.atten.linear", m_spotLights[i].GetLinearAttenuation());
		SetUniform(pointLightName + ".pLight.atten.exponent", m_spotLights[i].GetExponentAttenuation());
		SetUniform(pointLightName + ".pLight.position", m_spotLights[i].GetPosition());
		SetUniform(pointLightName + ".pLight.range", m_spotLights[i].GetRange());
		SetUniform(pointLightName + ".direction", m_spotLights[i].GetDirection());
		SetUniform(pointLightName + ".cutoff", m_spotLights[i].GetCutOff());
	}

}

void PhongShader::SetPointLights(PointLight* pointLights, int arraySize)
{
	if (arraySize > MAX_POINT_LIGHTS)
	{
		printf("Error: Too many point lights\n");
	}
	else
	{
		PhongShader::m_numPointLights = arraySize;
		PhongShader::m_pointLights = pointLights;
	}
}

void PhongShader::SetSpotLights(SpotLight* spotLights, int arraySize)
{
	if (arraySize > MAX_SPOT_LIGHTS)
	{
		printf("Error: Too many point lights\n");
	}
	else
	{
		PhongShader::m_numSpotLights = arraySize;
		PhongShader::m_spotLights = spotLights;
	}
}