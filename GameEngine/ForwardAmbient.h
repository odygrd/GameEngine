#ifndef FORWARDAMBIENT_H
#define FORWARDAMBIENT_H

#include "../rendering/shader.h"

class Material;

class ForwardAmbient : public Shader
{
public:
	static ForwardAmbient* GetInstance()
	{
		static ForwardAmbient instance;
		return  &instance;
	}

	virtual void UpdateUniforms(const mat4& modelmatrix, const Material& material) override;

private:
	ForwardAmbient();
	~ForwardAmbient();

	ForwardAmbient(ForwardAmbient const&){}
	void operator = (ForwardAmbient const&){}
};

#endif