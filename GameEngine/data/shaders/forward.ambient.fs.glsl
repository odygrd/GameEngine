#version 330
in vec2 out_texCoord;

uniform vec3 ambientIntensity;
uniform sampler2D sampler;

void main()
{
		 gl_FragColor = texture2D(sampler,out_texCoord.xy) * vec4(ambientIntensity,1);
}

