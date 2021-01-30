#include "AddShader.h"

AddShader::AddShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/PostProcessingShader.vert", "Assets/Shaders/AddShader.frag")
{
}

void AddShader::setTexture1(Texture& texture)
{
	texture.bind(0);
	setUniform("texture1", 0);
}

void AddShader::setTexture2(Texture& texture)
{
	texture.bind(1);
	setUniform("texture2", 1);
}