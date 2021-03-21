#include "ShadowShader.h"

ShadowShader::ShadowShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/ShadowShader.vert", "Assets/Shaders/ShadowShader.frag")
{}

void ShadowShader::setModelMatrix(const glm::mat4x4& matrix)
{
	setUniform("model", matrix);
}

void ShadowShader::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void ShadowShader::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}