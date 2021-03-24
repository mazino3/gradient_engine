#ifndef GRAPHICS_BYPASS_POSTPROCESSING_SHADER_H
#define GRAPHICS_BYPASS_POSTPROCESSING_SHADER_H

#include <Graphics/Shaders/Shader.h>
#include <Graphics/Texture.h>

struct BypassPostprocessingShader : Shader
{
	BypassPostprocessingShader();

	void setScreenTexture(Texture& texture);
};

#endif