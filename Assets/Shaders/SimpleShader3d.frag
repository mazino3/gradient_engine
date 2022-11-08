#version 130
precision highp float;

uniform vec3 drawColor;

out vec4 outColor;

void main(void) 
{
	outColor = vec4(drawColor, 1.0);
}