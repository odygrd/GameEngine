#ifndef FORWARDPOINT_H
#define FORWARDPOINT_H

#include "../rendering/shader.h"

class Material;

class ForwardPoint : public Shader
{
public:
	static ForwardPoint* GetInstance()
	{
		static ForwardPoint instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelmatrix, const Material& material) override;

private:
	ForwardPoint();
	~ForwardPoint();

	ForwardPoint(ForwardPoint const&){}
	void operator = (ForwardPoint const&){}
};

#endif