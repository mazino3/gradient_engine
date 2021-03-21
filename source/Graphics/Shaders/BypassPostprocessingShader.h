#ifndef GRAPHICS_BYPASS_POSTPROCESSING_SHADER_H
#define GRAPHICS_BYPASS_POSTPROCESSING_SHADER_H

#include "Shader.h"
#include "../Texture.h"

struct BypassPostprocessingShader : Shader
{
	BypassPostprocessingShader();

	void setScreenTexture(Texture& texture);
};

#endif