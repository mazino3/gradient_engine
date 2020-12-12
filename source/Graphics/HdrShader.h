#ifndef GRAPHICS_HDR_SHADER_H
#define GRAPHICS_HDR_SHADER_H

#include "Shader.h"
#include "Texture.h"

struct HdrShader : Shader
{
	HdrShader();

	void setScreenTexture(Texture& texture);
	void setToneMappingEnabled(bool enabled);
	void setGammaCorrectionEnabled(bool enabled);
	void setGamma(float gamma);
};

#endif