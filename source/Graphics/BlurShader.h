#ifndef GRAPHICS_BLUR_SHADER_H
#define GRAPHICS_BLUR_SHADER_H

#include "Shader.h"
#include "Texture.h"

struct BlurShader : Shader
{
	BlurShader();
	BlurShader(float radius);

	void setScreenTexture(Texture& texture);
	void setPixelSize(float pixelSize);
	void setHorizontal(bool isHorizontal);
};

#endif