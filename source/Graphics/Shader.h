#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <string>
#include <memory>

struct ShaderImpl;

enum class ShaderInitType
{
	Filename,
	Code
};

struct Shader
{
	Shader(ShaderInitType initType, std::string vertexShader, std::string fragmentShader);
	void bind();
	//todo: add uniform setters

private:

	std::shared_ptr<ShaderImpl> _data;
};

#endif