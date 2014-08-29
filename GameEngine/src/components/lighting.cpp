#include "lighting.h"
#include "../Rendering/renderEngine.h"
#include "../shaders/ForwardDirectional.h"
#include "../shaders/ForwardPoint.h"
#include "../shaders/forwardambient.h"
#include "../shaders/ForwardSpot.h"

void BaseLight::AddToRenderingEngine(RenderEngine* renderingEngine)
{
	renderingEngine->AddLight(this);
}

AmbientLight::AmbientLight(Color color, float intensity) : BaseLight(color, intensity)
{
	SetShader(ForwardAmbient::GetInstance());
};

DirectionalLight::DirectionalLight(Color color, vec3 direction, float intensity) : BaseLight(color, intensity), m_direction(glm::normalize(direction))
{
	SetShader(ForwardDirectional::GetInstance());
};

PointLight::PointLight(Color color, vec3 position, float intensity, float range, Attenuation attenuation) :
BaseLight(color, intensity), Attenuation(attenuation), m_position(position), m_range(range)
{
	SetShader(ForwardPoint::GetInstance());
};

SpotLight::SpotLight(Color color, vec3 position, vec3 direction, float intensity, float cutoff, float range, Attenuation attenuation) :
PointLight(color, position, intensity, range, attenuation), m_direction(glm::normalize(direction)), m_cutoff(cutoff)
{
	SetShader(ForwardSpot::GetInstance());
}