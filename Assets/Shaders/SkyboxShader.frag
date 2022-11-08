#version 130

in vec3 texCoords;
out vec4 outColor;

uniform samplerCube skybox;

void main(void)
{
	outColor = texture(skybox, texCoords);
}