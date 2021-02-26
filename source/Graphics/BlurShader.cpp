#include "BlurShader.h"

BlurShader::BlurShader() : Shader(ShaderInitType::Filename, "Assets/Shaders/BlurShader.vert", "Assets/Shaders/BlurShader.frag") 
{}

BlurShader::BlurShader(float radius)
{
	float sigma = radius / 3.0f;

	//todo: generate shader code...
}

void BlurShader::setScreenTexture(Texture& texture)
{
	texture.bind(0);
	setUniform("screenTexture", 0);
}

void BlurShader::setPixelSize(float pixelSize)
{
	setUniform("pixelSize", pixelSize);
}

void BlurShader::setHorizontal(bool isHorizontal)
{
	setUniform("isHorizontal", isHorizontal ? 1 : 0);
}