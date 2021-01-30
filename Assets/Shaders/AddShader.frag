#version 130

in vec2 texCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main(void)
{	
	gl_FragColor = texture(texture1, texCoords) + texture(texture2, texCoords);
}