#version 330
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

uniform vec3 basecolor;
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
uniform DirectionalLight directionalLight;

layout( location = 0 ) out vec4 FragColor;


vec4 CalculateLight(BaseLight base, vec3 direction, vec3 normal)
{
	vec3 s = normalize(direction);
	float sDotN  = max( dot(s, normal), 0.0 );
	vec4 diffuseColor = vec4(base.Color,1.0) * base.Intensity * sDotN ;

	return diffuseColor;
}

vec4 CalculateDirectionLight(DirectionalLight directionLight, vec3 normal)
{
	return CalculateLight(directionalLight.Base,directionalLight.Direction, normal);
}
void main()
{
    
    vec4 color = vec4(basecolor,1) *texture2D(sampler,TexCoord.xy);

	vec4 totalLight =  vec4(ambientLight,1) + CalculateDirectionLight(directionalLight, Normal);
    FragColor = color * totalLight;
}


