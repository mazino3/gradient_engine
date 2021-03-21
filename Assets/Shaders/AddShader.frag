#version 130

in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float multiplier1;
uniform float multiplier2;

void main(void)
{	
	gl_FragColor = vec4(texture(texture1, texCoords).xyz * multiplier1 + texture(texture2, texCoords).xyz * multiplier2, 1.0);
}