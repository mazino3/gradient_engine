#version 130

in vec2 texCoords;

uniform sampler2D screenTexture;
uniform bool toneMappingEnabled;
uniform bool gammaCorrectionEnabled;
uniform float gamma;

void main(void)
{
	vec3 color = texture(screenTexture, texCoords).rgb; 
	
	if (toneMappingEnabled)
	{
		color = color / (color + vec3(1.0));
	}
	
	if (gammaCorrectionEnabled)
	{
		color = pow(color, vec3(1.0 / gamma));
	}
	
	color = (color - 0.5) * (1.4) + 0.5;
	
	gl_FragColor = vec4(color, 1.0);
}