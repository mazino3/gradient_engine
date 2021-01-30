#include "FilterBrightShader.h"

FilterBrightShader::FilterBrightShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/PostProcessingShader.vert", "Assets/Shaders/PostProcessingShader.frag")
{
}

void FilterBrightShader::setScreenTexture(Texture& screenTexture)
{
	screenTexture.bind(0);
	setUniform("screenTexture", 0);
}

void FilterBrightShader::setBrightnessThreshold(float threshold)
{
	setUniform("brightnessThreshold", threshold);
}