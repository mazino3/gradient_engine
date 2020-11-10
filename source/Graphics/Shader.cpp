#include "Shader.h"
#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/ext.hpp>

struct ShaderImpl
{
	GLuint program;

	static GLuint currentProgram;
};

GLuint ShaderImpl::currentProgram = 0;

std::string readFile(const std::string& filename)
{
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);
	if (!file.good()) {
		std::cout << "Can't read file " << filename << std::endl;
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
		std::cout << "Error compiling shader: " << &shaderLog[0] << std::endl;
	}
	return shader;
}

Shader::Shader(ShaderInitType initType, std::string vertexShader, std::string fragmentShader)
{
    _data = std::make_shared<ShaderImpl>();

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
		std::cout << "Error linking shader: " << std::endl << &programLog[0] << std::endl;
	}

	_data->program = program;
}

void Shader::bind()
{
	ShaderImpl::currentProgram = _data->program;
	glUseProgram(_data->program);
}

void Shader::setUniform(const std::string& name, const glm::mat4x4& mat)
{
	if (_data->program != ShaderImpl::currentProgram)
	{
		std::cout << "error: setUniform is called without bind" << std::endl;
	}
	GLint location = glGetUniformLocation(_data->program, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}