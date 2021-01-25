#version 130

in vec3 in_Position;
in vec4 in_Color; //unused
in vec2 in_TexCoords;

out vec2 texCoords[11];

uniform float pixelSize;
uniform bool isHorizontal;

void main(void)
{
	gl_Position = vec4(in_Position, 1.0);
	vec2 centerTexCoords = in_Position.xy / 2 + 0.5;
	for(int i = -5; i <= 5; i++)
	{
		if (isHorizontal)
		{
			texCoords[i + 5] = centerTexCoords + vec2(pixelSize, 0.0);
		}
		else
		{
			texCoords[i + 5] = centerTexCoords + vec2(0.0, pixelSize);
		}
		
	}
}