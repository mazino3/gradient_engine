#version 130

in vec3 texCoords;

uniform samplerCube skybox;

void main(void)
{
	gl_FragColor = texture(skybox, texCoords);
}