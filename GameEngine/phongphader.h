#ifndef PHONGSHADER_H
#define PHONGSHADER_H

#include "shader.h"
#include "material.h"
#include "common.h"

class PhongShader : public Shader
{
public:
	static PhongShader* GetInstance()
	{
		static PhongShader instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& MVPMatrix, Material material);
	
	inline static const vec3& GetAmbientLight(){ return m_ambientLight; }
	inline static void SetAmbientLight(const vec3 ambientLight){ m_ambientLight = ambientLight; }
private:
	PhongShader();
	~PhongShader();

	PhongShader(PhongShader const&){}
	void operator = (PhongShader const&){}

	static vec3 m_ambientLight;
};

#endif