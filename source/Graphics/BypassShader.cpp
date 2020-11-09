#include "BypassShader.h"
#include <string>

static std::string vertexShader =
"#version 150\n" 
"in vec3 in_Position;\n" 
"in vec4 in_Color;\n" 
"out vec4 ex_Color;\n" 
"void main(void) {\n" 
"	gl_Position = vec4(in_Position, 1.0);\n" 
"	ex_Color = in_Color;\n"
"}";

static std::string fragmentShader =
"#version 150\n"
"precision highp float;\n"
"in vec4 ex_Color;\n"
"out vec4 gl_FragColor;\n"
"void main(void) {\n"
"	gl_FragColor = ex_Color;"
"}";

BypassShader::BypassShader() : Shader(ShaderInitType::Code, vertexShader, fragmentShader)
{}