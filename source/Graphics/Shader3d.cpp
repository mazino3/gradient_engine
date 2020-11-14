#include "Shader3d.h"
#include <string>

static std::string vertexShader =
"#version 130\n"
""
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"uniform mat4 model;\n"
""
"in vec3 in_Position;\n"
"in vec4 in_Color;\n"
"in vec2 in_TexCoord;\n"
"out vec4 ex_Color;\n"
"out vec2 ex_TexCoord;\n"
"void main(void) {\n"
"	gl_Position = projection * view * model * vec4(in_Position, 1.0);\n"
"	ex_Color = in_Color;\n"
"	ex_TexCoord = in_TexCoord;\n"
"}";

static std::string fragmentShader =
"#version 130\n"
"precision highp float;\n"
"uniform sampler2D diffuseTex;\n"
"in vec4 ex_Color;\n"
"in vec2 ex_TexCoord;\n"
"out vec4 gl_FragColor;\n"
"void main(void) {\n"
"	gl_FragColor = ex_Color * texture(diffuseTex, ex_TexCoord);\n"
"}";

Shader3d::Shader3d() : Shader(ShaderInitType::Code, vertexShader, fragmentShader)
{}

void Shader3d::setModelMatrix(const glm::mat4x4& matrix)
{
	setUniform("model", matrix);
}

void Shader3d::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void Shader3d::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}

void Shader3d::setDiffuseTexture(Texture& texture)
{
	texture.bind(0);
}