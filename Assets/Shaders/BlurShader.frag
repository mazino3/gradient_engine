#version 130

in vec2 texCoords[11];
out vec4 outColor;

uniform sampler2D screenTexture;


void main(void)
{	
	float kernel[11] = float[11](0.0093, 0.028002, 0.065984, 0.121703, 0.175713, 0.198596, 0.175713, 0.121703, 0.065984, 0.028002, 0.0093);
	gl_FragColor = vec4(0.0);
	for (int i = 0; i < 11; i++)
	{
		outColor += texture(screenTexture, texCoords[i]) * kernel[i];
	}
}