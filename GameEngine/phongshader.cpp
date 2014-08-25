#include "phongphader.h"

#include "texture.h"
#include "common.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };
vec3 PhongShader::m_ambientLight;
DirectionalLight PhongShader::m_directionalLight = DirectionalLight(vec3(0, 0, 0),vec3(0, 0, 0), 0);

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
}

PhongShader::~PhongShader()
{
}

void PhongShader::UpdateUniforms(const mat4& modelViewMatrix, const mat4& projectionMatrix, Material material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.GetTexture() != NULL)
		material.GetTexture()->Bind(0);
	else
	{
		WHITE.Bind(0);
	}

	SetUniform("MVP", projectionMatrix *modelViewMatrix);
	SetUniform("ModelViewMatrix", modelViewMatrix);
	SetUniform("NormalMatrix", mat3(vec3(modelViewMatrix[0]), vec3(modelViewMatrix[1]), vec3(modelViewMatrix[2])));
	SetUniform("basecolor", material.GetColor());
	SetUniform("ambientLight", m_ambientLight);
	SetUniform("directionalLight.Direction", m_directionalLight.GetDirection());
	SetUniform("directionalLight.Base.Color", m_directionalLight.GetColor());
	SetUniformf("directionalLight.Base.Intensity", m_directionalLight.GetIntensity());
}