#ifndef FORWARDDIRECTIONAL_H
#define FORWARDDIRECTIONAL_H

#include "../rendering/shader.h"
#include "../rendering/material.h"

class ForwardDirectional : public Shader
{
public:
	static ForwardDirectional* GetInstance()
	{
		static ForwardDirectional instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelmatrix, const Material& material);

private:
	ForwardDirectional();
	~ForwardDirectional();

	ForwardDirectional(ForwardDirectional const&){}
	void operator = (ForwardDirectional const&){}
};

#endif