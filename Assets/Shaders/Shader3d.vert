#version 130

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normalTm;

in vec3 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord;
in vec3 in_Normal;
out vec4 ex_Color;
out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_VertPos;


void main(void) 
{
	gl_Position = projection * view * model * vec4(in_Position, 1.0);
	ex_Color = in_Color;
	ex_TexCoord = in_TexCoord;
	ex_Normal = (normalTm * vec4(in_Normal, 1.0)).xyz;
	ex_VertPos = (view * model * vec4(in_Position, 1.0)).xyz;
}