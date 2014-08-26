#include "phongphader.h"

#include "../rendering/texture.h"
#include "../core/common.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };
vec3 PhongShader::m_ambientLight;
DirectionalLight PhongShader::m_directionalLight = DirectionalLight(vec3(0, 0, 0),vec3(0, 0, 0), 0);
PointLight* PhongShader::m_pointLights = NULL;
int PhongShader::m_numPointLights = 0;

PhongShader::PhongShader()
{
	AddVertexShaderFromFile("phongvertexshader.glsl");
	AddFragmentShaderFromFile("phongfragshader.glsl");
	LinkProgram();

	AddUniform("MVP");
	AddUniform("ModelViewMatrix");
	AddUniform("NormalMatrix");
	AddUniform("basecolor");
	AddUniform("ambientLight");
	AddUniform("directionalLight.Base.Color");
	AddUniform("directionalLight.Base.Intensity");
	AddUniform("directionalLight.Direction");
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePosition");

	for (int i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		AddUniform(pointLightName + ".Base.Color");
		AddUniform(pointLightName + ".Base.Intensity");
		AddUniform(pointLightName + ".Atten.Constant");
		AddUniform(pointLightName + ".Atten.Linear");
		AddUniform(pointLightName + ".Atten.Exponent");
		AddUniform(pointLightName + ".Position");
	}

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
	SetUniform("NormalMatrix", mat3(vec3(modelViewMatrix[0]), vec3(modelViewMatrix[1]), vec3(modelViewMatrix[2])));
	SetUniform("basecolor", material.GetColor());
	SetUniform("ambientLight", m_ambientLight);
	SetUniform("directionalLight.Direction", m_directionalLight.GetDirection());
	SetUniform("directionalLight.Base.Color", m_directionalLight.GetColor());
	SetUniformf("directionalLight.Base.Intensity", m_directionalLight.GetIntensity());
	SetUniformf("specularIntensity", material.GetSpecularIntensity());
	SetUniformf("specularPower", material.GetSpecularPower());
	SetUniform("eyePosition", cameraPosition);


	for (int i = 0; i < m_numPointLights; i++)
	{
		std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

		SetUniform(pointLightName + ".Base.Color", m_pointLights[i].GetColor());
		SetUniformf(pointLightName + ".Base.Intensity", m_pointLights[i].GetIntensity());
		SetUniformf(pointLightName + ".Atten.Constant", m_pointLights[i].GetConstantAttenuation());
		SetUniformf(pointLightName + ".Atten.Linear", m_pointLights[i].GetLinearAttenuation());
		SetUniformf(pointLightName + ".Atten.Exponent", m_pointLights[i].GetExponentAttenuation());
		SetUniform(pointLightName + ".Position", m_pointLights[i].GetPosition());
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