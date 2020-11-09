#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>

struct ShaderImpl
{
	GLuint program;
};

std::string readFile(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);
	if (!file.good()) {
		std::cerr << "Can't read file " << filename << std::endl;
		std::terminate();
	}
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint createShader(GLenum shaderType, const std::string& source)
{
	int compileResult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char* shaderCodePtr = source.c_str();
	int shaderCodeSize = source.size();
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		std::cerr << "Error compiling shader: " << &shaderLog[0] << std::endl;
	}
	return shader;
}

Shader::Shader(ShaderInitType initType, std::string vertexShader, std::string fragmentShader)
{
	if (initType == ShaderInitType::Filename)
	{
		vertexShader = readFile(vertexShader);
		fragmentShader = readFile(fragmentShader);
	}

	GLuint vertexShaderHandle = createShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fragmentShaderHandle = createShader(GL_FRAGMENT_SHADER, fragmentShader);

	int linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShaderHandle);
	glAttachShader(program, fragmentShaderHandle);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE)
	{
		int infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::cerr << "Error linking shader: " << std::endl << &programLog[0] << std::endl;
	}

	_data->program = program;
}

void Shader::bind()
{
	glUseProgram(_data->program);
}