#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

layout( location = 0 ) out vec4 FragColor;

struct BaseLight 
{
	vec3 color;
	float intensity;
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


uniform vec3 eyePosition;
uniform float specularIntensity;
uniform float specularPower;
uniform sampler2D diffuse;
uniform PointLight pointlight;

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

void main()
{
    FragColor =  texture2D(diffuse,vertexTexCoord.xy) * CalculatePointLight(pointlight);
}