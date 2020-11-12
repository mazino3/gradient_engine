#include "Shader3d.h"
#include <string>

static std::string vertexShader =
"#version 130\n"
""
"uniform mat4 projection;"
"uniform mat4 view;"
"uniform mat4 model;"
""
"in vec3 in_Position;\n"
"in vec4 in_Color;\n"
"out vec4 ex_Color;\n"
"void main(void) {\n"
"	gl_Position = projection * view * model * vec4(in_Position, 1.0);\n"
"	ex_Color = in_Color;\n"
"}";

static std::string fragmentShader =
"#version 130\n"
"precision highp float;\n"
"in vec4 ex_Color;\n"
"out vec4 gl_FragColor;\n"
"void main(void) {\n"
"	gl_FragColor = ex_Color;"
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