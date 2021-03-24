#include <Graphics/Shaders/BypassPostprocessingShader.h>

BypassPostprocessingShader::BypassPostprocessingShader() :
	Shader(ShaderInitType::Filename, "Assets/Shaders/PostProcessingShader.vert", "Assets/Shaders/BypassPostprocessingShader.frag")
{}

void BypassPostprocessingShader::setScreenTexture(Texture& texture)
{
	texture.bind(0);
	setUniform("screenTexture", 0);
}