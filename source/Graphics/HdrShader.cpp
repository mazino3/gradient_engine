#include "HdrShader.h"

HdrShader::HdrShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/PostProcessingShader.vert", "Assets/Shaders/HdrShader.frag")
{}

void HdrShader::setScreenTexture(Texture& texture)
{
	texture.bind(0);
	setUniform("screenTexture", 0);
}

void HdrShader::setToneMappingEnabled(bool enabled)
{
	setUniform("toneMappingEnabled", enabled ? 1 : 0);
}

void HdrShader::setGammaCorrectionEnabled(bool enabled)
{
	setUniform("gammaCorrectionEnabled", enabled ? 1 : 0);
}

void HdrShader::setGamma(float gamma)
{
	setUniform("gamma", gamma);
}