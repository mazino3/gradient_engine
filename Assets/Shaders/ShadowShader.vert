#version 130

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec3 in_Position;

void main(void) 
{
	gl_Position = projection * view * model * vec4(in_Position, 1.0);
}