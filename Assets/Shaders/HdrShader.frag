#version 130

in vec2 texCoords;

uniform sampler2D screenTexture;

void main(void)
{
	gl_FragColor = texture(screenTexture, texCoords);
}