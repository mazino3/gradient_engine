#version 130

in vec2 texCoords;

uniform sampler2D outlineTexture;
uniform sampler2D screenTexture;

uniform vec3 outlineColor;

void main(void)
{	
	float outlineValue = texture(outlineTexture, texCoords).r;
	gl_FragColor = vec4(outlineColor, 1.0) * outlineValue + texture(screenTexture, texCoords) * (1.0 - outlineValue);
}