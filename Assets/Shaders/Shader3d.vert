#version 130

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 normalTm;

uniform bool textureScalingEnabled;
uniform vec3 textureScale;

in vec3 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord;
in vec3 in_Normal;
in vec3 in_Tangent;
in vec3 in_Bitangent;
out vec4 ex_Color;
out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_Tangent;
out vec3 ex_Bitangent;
out vec3 ex_VertPos;


void main(void) 
{
	gl_Position = projection * view * model * vec4(in_Position, 1.0);
	ex_Color = in_Color;
	if (textureScalingEnabled)
	{
		float texMultX = 1.0;
		float texMultY = 1.0;
		if (in_Normal.x != 0.0)
		{
			texMultX = textureScale.y;
			texMultY = textureScale.z;
		}
		if (in_Normal.y != 0.0)
		{
			texMultX = textureScale.x;
			texMultY = textureScale.z;
		}
		if (in_Normal.z != 0.0)
		{
			texMultX = textureScale.x;
			texMultY = textureScale.y;
		}
		ex_TexCoord = vec2(in_TexCoord.x * texMultX, in_TexCoord.y * texMultY);
	}
	else
	{
		ex_TexCoord = in_TexCoord;
	}
	ex_Normal = (normalTm * vec4(in_Normal, 1.0)).xyz;
	ex_Tangent = (normalTm * vec4(in_Tangent, 1.0)).xyz;
	ex_Bitangent = (normalTm * vec4(in_Bitangent, 1.0)).xyz;
	ex_VertPos = (view * model * vec4(in_Position, 1.0)).xyz;
}