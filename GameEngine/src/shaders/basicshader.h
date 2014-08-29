#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "../rendering/shader.h"
class Material;

class BasicShader : public Shader
{
public:
	static BasicShader* GetInstance()
	{
		static BasicShader instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelmatrix,const Material& material) override;
	
private:
	BasicShader();
	~BasicShader();

	BasicShader(BasicShader const&){}
	void operator = (BasicShader const&){}
};

#endif