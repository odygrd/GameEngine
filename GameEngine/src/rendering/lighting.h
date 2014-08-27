#ifndef LIGHTING_H
#define LIGHTING_H

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

class AmbientLight : public BaseLight
{
public:
	AmbientLight(){};
	AmbientLight(float intensity , vec3 color = vec3(1.0,1.0,1.0)) :BaseLight(color, intensity){};
};

class DirectionalLight : public BaseLight
{
public:
	DirectionalLight():m_direction(vec3(0.0f,0.0f,0.0f)){};
	DirectionalLight(vec3 direction, vec3 color, float intensity) : BaseLight(color, intensity), m_direction(glm::normalize(direction)){};
	inline const vec3& GetDirection() const { return m_direction; }
	inline void SetDirection(const vec3& direction){ m_direction = glm::normalize(direction); }
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

	inline void SetConstantAttenuation(float constant) { m_constant = constant; }
	inline void SetLinearAttenuation(float linear) { m_linear = linear; }
	inline void SetExponentAttenuation(float exponent) { m_exponent = exponent; }
private:
	float m_constant;
	float m_linear;
	float m_exponent;
};

class PointLight : public BaseLight, public Attenuation
{
public:
	PointLight(){};
	PointLight(vec3 position, vec3 color, float range, float intensity, float constantAttenuation = 0, float linearAttenuation = 0, float exponentAttenuation = 1) :
		BaseLight(color, intensity), Attenuation(constantAttenuation, linearAttenuation, exponentAttenuation), m_position(position), m_range(range){};
	inline const vec3& GetPosition() const { return m_position; }
	inline float GetRange() const { return m_range; }

	inline void SetPosition(const vec3& position){ m_position = position; }
	inline void SetRange(float range){ m_range = range; }
private:
	vec3 m_position;
	float m_range;
};

class SpotLight : public PointLight
{
public:
	SpotLight():m_direction(vec3(0.0f,0.0f,0.0f)),m_cutoff(0.0f){};
	SpotLight(vec3 position, vec3 direction, vec3 color, float intensity, float cutoff, float range, float constantAttenuation = 0, float linearAttenuation = 0, float exponentAttenuation = 0.1) :
		PointLight(position, color, range, intensity, constantAttenuation, linearAttenuation, exponentAttenuation), m_direction(glm::normalize(direction)), m_cutoff(cutoff){};
	inline const vec3& GetDirection() const { return m_direction; }
	inline float GetCutOff() {return m_cutoff; }

	inline void SetDirection(const vec3& direction){ m_direction = glm::normalize(direction); }
	inline void SetCutOff(float cutoff){ m_cutoff = cutoff; }

private:
	vec3 m_direction;
	float m_cutoff;
};

#endif