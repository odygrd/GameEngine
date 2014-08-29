#ifndef MATERIAL_H
#define MATERIAL_H
#include "../core/common.h"

class Texture;

class Material
{
public:
	Material(){};
	Material(Texture* texture, const vec3& color = vec3(1, 1, 1), float specIntensity = 0, float specPower = 0) : 
		m_texture(texture), m_color(color), m_specularIntensity(specIntensity), m_specularPower(specPower){};
	
	inline Texture* GetTexture() const { return m_texture; }
	inline const vec3& GetColor() const { return m_color; }
	inline float GetSpecularIntensity() const { return m_specularIntensity; }
	inline float GetSpecularPower() const { return m_specularPower; }

private:
	Texture* m_texture;
	vec3 m_color;
	float m_specularIntensity;
	float m_specularPower;
};

#endif