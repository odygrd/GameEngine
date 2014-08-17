#include "phongphader.h"

#include "texture.h"
#include "common.h"

static BYTE whitePixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };
vec3 PhongShader::m_ambientLight;

PhongShader::PhongShader()
{
	AddVertexShaderFromFile("phongvertexshader.glsl");
	AddFragmentShaderFromFile("phongfragshader.glsl");
	LinkProgram();

	AddUniform("MVPMatrix");
	AddUniform("basecolor");
	AddUniform("ambientLight");
}

PhongShader::~PhongShader()
{
}

void PhongShader::UpdateUniforms(const mat4& MVPMatrix, Material material)
{
	static Texture WHITE = Texture(1, 1, whitePixel);

	if (material.GetTexture() != NULL)
		material.GetTexture()->Bind(0);
	else
	{
		WHITE.Bind(0);
	}

	SetUniform("MVPMatrix", MVPMatrix);
	SetUniform("basecolor", material.GetColor());
	SetUniform("ambientLight", m_ambientLight);
}