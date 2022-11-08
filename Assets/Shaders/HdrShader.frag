#version 130

in vec2 texCoords;
out vec4 outColor;

uniform sampler2D screenTexture;
uniform bool toneMappingEnabled;
uniform bool gammaCorrectionEnabled;
uniform float gamma;
uniform float contrast;
uniform float exposure;

void main(void)
{
	vec3 color = texture(screenTexture, texCoords).rgb; 
	
	if (toneMappingEnabled)
	{
		color *= exposure;
		color = color / (color + vec3(1.0));
	}
	
	if (gammaCorrectionEnabled)
	{
		color = pow(color, vec3(1.0 / gamma));
	}
	
	color = (color - 0.5) * (1.0 + contrast) + 0.5;
	
	outColor = vec4(color, 1.0);
}