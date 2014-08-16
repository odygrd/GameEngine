#version 330
in vec2 out_texCoord;

uniform vec3 color;
uniform sampler2D sampler;

void main()
{
    vec4 textureColor = texture2D(sampler,out_texCoord.xy);

    if(textureColor == vec4(0,0,0,1))
		 gl_FragColor = vec4(color,1);
    else
		 gl_FragColor = texture2D(sampler,out_texCoord.xy) * vec4(color,1);
}

