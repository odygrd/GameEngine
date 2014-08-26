#ifndef LIGHTING_H
#define LIGHTING_H
#include "../core/common.h"

class BaseLight
{
public:
	BaseLight() : m_color(vec3(1.0f, 1.0f, 1.0f)), m_intensity(0.0f){};
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
	DirectionalLight(){};
	DirectionalLight(vec3 direction, vec3 color, float intensity) : BaseLight(color, intensity), m_direction(direction){};
	inline const vec3& GetDirection() const { return m_direction; }
	inline void SetDirection(const vec3& direction){ m_direction = direction; }
private:
	vec3 m_direction;
};

class Attenuation
{
public:
	Attenuation() :m_constant(0.0f), m_linear(0.0f), m_exponent(1.0f){};
	Attenuation(float constant, float linear, float exponent) : m_constant(constant), m_linear(linear), m_exponent(exponent){};
	inline float GetConstantAttenuation() const{ return  m_constant; }
	inline float GetLinearAttenuation() const{ return m_linear; }
	inline float GetExponentAttenuation() const{ return m_exponent; }
private:
	float m_constant;
	float m_linear;
	float m_exponent;
};

class PointLight : public BaseLight, public Attenuation
{
public:
	PointLight(){};
	PointLight(vec3 position, vec3 color, float intensity, float constantAttenuation = 0, float linearAttenuation = 0, float exponentAttenuation = 1) :
		BaseLight(color, intensity), Attenuation(constantAttenuation, linearAttenuation, exponentAttenuation), m_position(position){};
	inline const vec3& GetPosition() const { return m_position; }
	inline void SetPosition(const vec3& position){ m_position = position; }
private:
	vec3 m_position;
};

#endif