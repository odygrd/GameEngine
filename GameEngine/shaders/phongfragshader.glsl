#version 330
in vec2 out_texCoord;
out vec4 fragmentColor;

uniform vec3 basecolor;
uniform vec3 ambientLight;
uniform sampler2D sampler;

void main()
{
    vec4 totalLight = vec4(ambientLight,1);
    vec4 color = vec4(basecolor,1);
    vec4 textureColor = texture2D(sampler,out_texCoord.xy);
    if(textureColor != vec4(0,0,0,0))
	color *= textureColor;
    fragmentColor = color * totalLight;
}


