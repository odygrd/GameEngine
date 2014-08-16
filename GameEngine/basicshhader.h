#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "shader.h"
#include "material.h"
#include "common.h"

class BasicShader : public Shader
{
public:
	static BasicShader* GetInstance()
	{
		static BasicShader instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& MVPMatrix, Material material);
	void operator = (BasicShader const&){}
private:
	BasicShader();
	~BasicShader();

	BasicShader(BasicShader const&){}
	
};

#endif