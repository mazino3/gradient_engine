#version 130

in vec3 in_Position;
in vec4 in_Color; //unused
in vec2 in_TexCoords;

out vec2 texCoords;

void main(void)
{
	texCoords = in_TexCoords;
	gl_Position = vec4(in_Position, 1.0);
}