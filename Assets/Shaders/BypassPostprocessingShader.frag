#version 130

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D screenTexture;

void main(void)
{	
	outColor = texture(screenTexture, texCoords);
}