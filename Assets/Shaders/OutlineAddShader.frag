#version 130

in vec2 texCoords;

uniform sampler2D outlineTexture;
uniform sampler2D screenTexture;

uniform vec3 outlineColor;

void main(void)
{	
	gl_FragColor = outlineColor * texture(outlineTexture, texCoords).r + screenTexture * (1.0 - texture(outlineTexture, texCoords).r);
}