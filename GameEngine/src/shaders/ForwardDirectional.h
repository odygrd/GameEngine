#ifndef FORWARDDIRECTIONAL_H
#define FORWARDDIRECTIONAL_H

#include "../rendering/shader.h"

class Material;

class ForwardDirectional : public Shader
{
public:
	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelmatrix, const Material& material) override;

private:
	ForwardDirectional();
	~ForwardDirectional();

	ForwardDirectional(ForwardDirectional const&){}
	void operator = (ForwardDirectional const&){}
};

#endif