#ifndef LIGHTING_H
#define LIGHTING_H
#include "common.h"

class BaseLight
{
public:
	BaseLight(vec3 color, float intensity) : m_color(color), m_intensity(intensity){};
	inline const vec3& GetColor() const { return m_color; }
	inline float GetIntensity() const { return m_intensity; }

	inline void SetColor(const vec3& color){ m_color = color; }
	inline void SetIntensity(float intensity){ m_intensity = intensity; }
private:
	vec3 m_color;
	float m_intensity;
};

class DirectionalLight : public BaseLight
{
public:
	DirectionalLight(vec3 direction, vec3 color, float intensity) : BaseLight(color, intensity), m_direction(direction){};
	inline const vec3& GetDirection() const { return m_direction; }
	inline void SetDirection(const vec3& direction){ m_direction = direction; }
private:
	vec3 m_direction;
};


#endif