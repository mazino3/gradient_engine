#version 130

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D outlineTexture;
uniform sampler2D screenTexture;

uniform vec3 outlineColor;

void main(void)
{	
	float outlineValue = texture(outlineTexture, texCoords).r;
	outColor = vec4(outlineColor, 1.0) * outlineValue + texture(screenTexture, texCoords) * (1.0 - outlineValue);
}