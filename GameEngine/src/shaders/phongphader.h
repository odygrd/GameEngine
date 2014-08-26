#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "../rendering/shader.h"
#include "../rendering/material.h"
#include "../core/common.h"
#include "../rendering/lighting.h"

class PhongShader : public Shader
{
public:
	static PhongShader* GetInstance()
	{
		static PhongShader instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelViewMatrix, const mat4& projectionMatrix, const vec3& cameraPosition, const Material& material);
	
	inline static const vec3& GetAmbientLight(){ return m_ambientLight; }
	inline static void SetAmbientLight(const vec3& ambientLight){ m_ambientLight = ambientLight; }

	inline static void PhongShader::SetDirectionalLight(const DirectionalLight& directionalLight){ m_directionalLight = directionalLight;}
	static void SetPointLights(PointLight* pointLights, int arraySize);
private:
	PhongShader();
	~PhongShader();

	PhongShader(PhongShader const&){}
	void operator = (PhongShader const&){}

	static vec3 m_ambientLight;
	static DirectionalLight m_directionalLight;
	static PointLight* m_pointLights;

	static const int MAX_POINT_LIGHTS = 4;
	static int m_numPointLights;
};

#endif