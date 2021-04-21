#version 130

uniform mat4 projection;
uniform mat4 view;
uniform vec3 pos1;
uniform vec3 pos2;

in vec3 in_Position;

void main(void) 
{
	vec3 modelPos = in_Position.x * pos1 + (1.0 - in_Position.x) * pos2;
	gl_Position = projection * view * vec4(modelPos, 1.0);
}