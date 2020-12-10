#version 130

in vec3 in_Position;

out vec3 texCoords;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main(void)
{
	texCoords = vec3(model * vec4(in_Position, 1.0)).xzy;
	vec4 pos = projection * view * model * vec4(in_Position, 1.0);
	gl_Position = pos.xyww;
}