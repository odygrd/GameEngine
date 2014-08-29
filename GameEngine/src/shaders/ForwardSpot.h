#ifndef FORWARDSPOT_H
#define FORWARDSPOT_H

#include "../rendering/shader.h"
class Material;
class ForwardSpot : public Shader
{
public:
	static ForwardSpot* GetInstance()
	{
		static ForwardSpot instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelmatrix, const Material& material) override;

private:
	ForwardSpot();
	~ForwardSpot();

	ForwardSpot(ForwardSpot const&){}
	void operator = (ForwardSpot const&){}
};

#endif