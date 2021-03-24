#include <Graphics/Shaders/SimpleShader3d.h>

SimpleShader3d::SimpleShader3d() : Shader(ShaderInitType::Filename, "Assets/Shaders/SimpleShader3d.vert", "Assets/Shaders/SimpleShader3d.frag")
{
}

void SimpleShader3d::setModelMatrix(const glm::mat4x4& matrix)
{
	setUniform("model", matrix);
}

void SimpleShader3d::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void SimpleShader3d::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}

void SimpleShader3d::setNormalMatrix(const glm::mat4x4& matrix)
{
	setUniform("normalTm", matrix);
}

void SimpleShader3d::setEyeDirection(const glm::vec3& eyeDirection)
{
	setUniform("eyeDirection", eyeDirection);
}

void SimpleShader3d::setColor(const glm::vec3& color)
{
	setUniform("drawColor", color);
}
