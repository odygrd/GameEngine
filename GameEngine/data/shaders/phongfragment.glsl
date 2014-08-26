#version 330
const int MAX_POINT_LIGHTS = 4;
const int MAX_SPOT_LIGHTS = 4;

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

struct BaseLight 
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
	BaseLight base;
	Attenuation atten;
	vec3 position;
	float range;
};

struct SpotLight
{
	PointLight pLight;
	vec3 direction;
	float cutoff;
};

uniform vec3 basecolor;
uniform vec3 eyePosition;
uniform float specularIntensity;
uniform float specularPower;
uniform sampler2D sampler;
uniform BaseLight ambientLight;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

layout( location = 0 ) out vec4 FragColor;

vec4 CalculateLight(BaseLight base, vec3 direction)
{
	float sDotN  = max( dot(direction, vertexNormal), 0.0 );
	vec4 diffuseSpecular = vec4(0.0,0.0,0.0,0.0);
	if (sDotN > 0.0)
	{
		//Diffuse Color
		diffuseSpecular = vec4(base.color,1.0) * base.intensity * sDotN ;

		vec3 v = normalize(eyePosition - vertexPosition);
		vec3 h = normalize(v + direction); //half vector
		// vec3 r = normalize(reflect( -s, vertexNormal ));
		//Specular Color
		diffuseSpecular += vec4(base.color,1.0) * specularIntensity * pow( max( dot(h,vertexNormal), 0.0 ), specularPower );
		//diffuseSpecular += vec4(base.Color,1.0) * specularIntensity * pow( max( dot(v,r), 0.0 ), specularPower );
	}
	return diffuseSpecular;
}

vec4 CalculateDirectionLight(DirectionalLight directionLight)
{
	return CalculateLight(directionalLight.base, directionalLight.direction);
}

vec4 CalculatePointLight(PointLight pointlight)
{
	vec3 lightDirection = pointlight.position - vertexPosition;
	float distanceToPoint = length(lightDirection);
	lightDirection = normalize(lightDirection);

	if ( distanceToPoint > pointlight.range) 
	{
		return vec4(0,0,0,0);
	}

	vec4 color = CalculateLight(pointlight.base, lightDirection);

	float attenuation = pointlight.atten.constant +
						pointlight.atten.linear * distanceToPoint +
						pointlight.atten.exponent * distanceToPoint * distanceToPoint +
						0.0001;
	return color / attenuation;
}

vec4 CalculateSpotLight(SpotLight sLight)
{
	vec3 lightDirection = normalize (sLight.pLight.position - vertexPosition);
	float spotFactor = dot(lightDirection, sLight.direction);
	vec4 color = vec4(0,0,0,0);
	if (spotFactor > sLight.cutoff)
	{
		color = CalculatePointLight(sLight.pLight) * 
				(1.0 - (1.0 - spotFactor) / (1.0 - sLight.cutoff));
	}
	return color;
}
void main()
{
    vec4 color = vec4(basecolor,1) *texture2D(sampler,vertexTexCoord.xy);

	vec4 totalLight =  vec4(ambientLight.color,1.0f) * ambientLight.intensity;
	totalLight += CalculateDirectionLight(directionalLight);

	for(int i=0; i <MAX_POINT_LIGHTS; i++)
	{
	   if(pointLights[i].base.intensity > 0)
	   {
			totalLight += CalculatePointLight(pointLights[i]);
	   }
	}

	for(int i=0; i <MAX_SPOT_LIGHTS; i++)
	{
	   if(spotLights[i].pLight.base.intensity > 0)
	   {
			totalLight += CalculateSpotLight(spotLights[i]);
	   }
	}

    FragColor = color * totalLight;
}


