#version 130
precision highp float;

uniform vec3 drawColor;

out vec4 gl_FragColor;

void main(void) 
{
	gl_FragColor = vec4(drawColor, 1.0);
}