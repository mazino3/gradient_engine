#include "OutlineAddShader.h"

OutlineAddShader::OutlineAddShader() :
	Shader(ShaderInitType::Filename, "Assets/Shaders/PostProcessingShader.vert", "Assets/Shaders/OutlineAddShader.frag")
{}

void OutlineAddShader::setOutlineTexture(Texture& texture)
{
	texture.bind(0);
	setUniform("outlineTexture", 0);
}

void OutlineAddShader::setScreenTexture(Texture& texture)
{
	texture.bind(1);
	setUniform("screenTexture", 1);
}

void OutlineAddShader::setOutlineColor(const glm::vec3& outlineColor)
{
	setUniform("outlineColor", outlineColor);
}