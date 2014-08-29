#ifndef LIGHTING_H
#define LIGHTING_H
#include "component.h"
#include "../core/common.h"

class Shader;

class BaseLight : public GameComponent
{
public:
	BaseLight() : m_color(1.0f,1.0f,1.0f), m_intensity(0.0f){};
	BaseLight(Color color, float intensity) : m_color(color), m_intensity(intensity){};

	inline const Color& GetColor() const { return m_color; }
	inline float GetIntensity() const { return m_intensity; }
	inline Shader* GetShader() const { return m_shader; }

	inline void SetColor(const Color& color){ m_color = color; }
	inline void SetIntensity(float intensity){ m_intensity = intensity; }
	inline void SetShader(Shader* shader) { m_shader = shader; }
	inline virtual void AddToRenderingEngine(RenderEngine* renderingEngine) override;
	
private:
	Color m_color;
	float m_intensity;
	Shader* m_shader;
};

class AmbientLight : public BaseLight
{
public:
	explicit AmbientLight(Color color = Color(0.1f, 0.1f, 0.1f), float intensity = 0.0f);
};

class DirectionalLight : public BaseLight
{
public:
	DirectionalLight():m_direction(vec3(0.0f,0.0f,0.0f)){};
	DirectionalLight(Color color, vec3 direction, float intensity);

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
	Attenuation(const Attenuation& attenuation) : m_constant(attenuation.GetConstantAttenuation()), m_linear(attenuation.GetLinearAttenuation()), m_exponent(attenuation.GetExponentAttenuation()){};

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
	PointLight(Color color, vec3 position, float intensity, float range, Attenuation attenuation = Attenuation(0.0f, 0.0f, 1.0f));
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
	SpotLight(){};
	SpotLight(Color color, vec3 position, vec3 direction, float intensity, float cutoff, float range, Attenuation attenuation = Attenuation(0.0f, 0.0f, 1.0f));
	inline const vec3& GetDirection() const { return m_direction; }
	inline float GetCutOff() const {return m_cutoff; }

	inline void SetDirection(const vec3& direction){ m_direction = glm::normalize(direction); }
	inline void SetCutOff(float cutoff){ m_cutoff = cutoff; }

private:
	vec3 m_direction;
	float m_cutoff;
};

#endif