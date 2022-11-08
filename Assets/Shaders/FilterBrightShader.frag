#version 130

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D screenTexture;
uniform float brightnessThreshold;

void main(void)
{	
	vec4 color = texture(screenTexture, texCoords);
	float brightness = (color.r * 0.2126 + color.g * 0.7152 + color.b * 0.0722);
	if (brightness > brightnessThreshold)
	{
		outColor = color;
	}
	else
	{
		outColor = vec4(0.0);
	}
}