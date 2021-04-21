#include <Graphics/Shaders/LineShader3d.h>

LineShader3d::LineShader3d() : Shader(ShaderInitType::Filename, "Assets/Shaders/LineShader3d.vert", "Assets/Shaders/LineShader3d.frag")
{}

void LineShader3d::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void LineShader3d::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}

void LineShader3d::setPos1(const glm::vec3& pos)
{
	setUniform("pos1", pos);
}

void LineShader3d::setPos2(const glm::vec3& pos)
{
	setUniform("pos1", pos);
}

void LineShader3d::setColor(const glm::vec3& color)
{
	setUniform("drawColor", color);
}

