#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <string>
#include <memory>
#include <glm/mat4x4.hpp>

struct ShaderImpl;

enum class ShaderInitType
{
	Filename,
	Code
};

struct Shader
{
	Shader(ShaderInitType initType, std::string vertexShader, std::string fragmentShader);
	Shader();
	virtual ~Shader() {}

	virtual void bind();
	//todo: add more uniform setters
	void setUniform(const std::string& name, const glm::mat4x4& mat);
	void setUniform(const std::string& name, const glm::vec3& vec3);
	void setUniform(const std::string& name, float value);
	void setUniform(const std::string& name, int value);

protected:
	virtual void init(ShaderInitType initType, std::string vertexShader, std::string fragmentShader);

private:

	std::shared_ptr<ShaderImpl> _data;
};

#endif