#include <Graphics/Shaders/SkyboxShader.h>

SkyboxShader::SkyboxShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/SkyboxShader.vert", "Assets/Shaders/SkyboxShader.frag")
{}

void SkyboxShader::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void SkyboxShader::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}

void SkyboxShader::setModelMatrix(const glm::mat4x4& matrix)
{
	setUniform("model", matrix);
}

void SkyboxShader::setSkyboxCubemap(CubeMap& cubemap)
{
	cubemap.bind(0);
	setUniform("skybox", 0);
}