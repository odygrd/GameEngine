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
	
	inline static void SetAmbientLight(const AmbientLight& ambientLight){ m_ambientLight = ambientLight; }

	inline static void PhongShader::SetDirectionalLight(const DirectionalLight& directionalLight){ m_directionalLight = directionalLight;}
	static void SetPointLights(PointLight* pointLights, int arraySize);
	static void SetSpotLights(SpotLight* spotLights, int arraySize);

private:
	PhongShader();
	~PhongShader();

	PhongShader(PhongShader const&){}
	void operator = (PhongShader const&){}

	static AmbientLight m_ambientLight;
	static DirectionalLight m_directionalLight;
	static PointLight* m_pointLights;
	static SpotLight* m_spotLights;

	static const int MAX_POINT_LIGHTS = 4;
	static const int MAX_SPOT_LIGHTS = 4;
	static int m_numPointLights;
	static int m_numSpotLights;
};

#endif