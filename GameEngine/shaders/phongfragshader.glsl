#version 330
const int MAX_POINT_LIGHTS = 4;

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

uniform vec3 basecolor;
uniform vec3 eyePosition;
uniform vec3 ambientLight;
uniform sampler2D sampler;

struct BaseLight 
{
	vec3 Color;
	float Intensity;
};

struct DirectionalLight
{
	BaseLight Base;
	vec3 Direction;
};

uniform float specularIntensity;
uniform float specularPower;

struct Attenuation
{
	float Constant;
	float Linear;
	float Exponent;
};

struct PointLight
{
	BaseLight Base;
	Attenuation Atten;
	vec3 Position;
};

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];

layout( location = 0 ) out vec4 FragColor;

vec4 CalculateLight(BaseLight base, vec3 direction, vec3 normal)
{
	vec3 s = normalize(direction);
	float sDotN  = max( dot(normal, direction), 0.0 );
	vec4 diffuseSpecular = vec4(0.0,0.0,0.0,0.0);
	if (sDotN > 0.0)
	{
	//Diffuse Color
		diffuseSpecular = vec4(base.Color,1.0) * base.Intensity * sDotN ;

		vec3 v = normalize(eyePosition - Position);
		vec3 h = normalize(v + s); //half vector
		// vec3 r = normalize(reflect( -s, normal ));
    //Specular Color
		diffuseSpecular += vec4(base.Color,1.0) * specularIntensity * pow( max( dot(h,normal), 0.0 ), specularPower );
		//diffuseSpecular += vec4(base.Color,1.0) * specularIntensity * pow( max( dot(v,r), 0.0 ), specularPower );
	}

	return diffuseSpecular;
}

vec4 CalculateDirectionLight(DirectionalLight directionLight, vec3 normal)
{
	return CalculateLight(directionalLight.Base,directionalLight.Direction, normal);
}

vec4 CalculatePointLight(PointLight pointlight, vec3 normal)
{
	vec3 lightDirection = pointlight.Position - Position;
	float distanceToPoint = length(lightDirection);

	vec4 color = CalculateLight(pointlight.Base, lightDirection, normal);

	float attenuation = pointlight.Atten.Constant +
						pointlight.Atten.Linear * distanceToPoint +
						pointlight.Atten.Exponent * distanceToPoint * distanceToPoint +
						0.0001;
	return color / attenuation;
}

void main()
{
    
    vec4 color = vec4(basecolor,1) *texture2D(sampler,TexCoord.xy);

	vec4 totalLight =  vec4(ambientLight,1) + CalculateDirectionLight(directionalLight, Normal);
	for(int i=0; i <MAX_POINT_LIGHTS; i++)
	{
	   if(pointLights[i].Base.Intensity > 0)
	   {
		totalLight += CalculatePointLight(pointLights[i], Normal);
	   }
	}
    FragColor = color * totalLight;
}


