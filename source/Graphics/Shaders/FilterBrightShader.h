#ifndef GRAPHICS_FILTER_BRIGHT_SHADER_H
#define GRAPHICS_FILTER_BRIGHT_SHADER_H

#include "Shader.h"
#include "../Texture.h"

struct FilterBrightShader : Shader
{
	FilterBrightShader();

	void setScreenTexture(Texture& screenTexture);
	void setBrightnessThreshold(float threshold);
};

#endif