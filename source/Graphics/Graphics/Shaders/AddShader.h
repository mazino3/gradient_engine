#ifndef GRAPHICS_ADD_SHADER_H
#define GRAPHICS_ADD_SHADER_H

#include <Graphics/Shaders/Shader.h>
#include <Graphics/Texture.h>

struct AddShader : Shader
{
	AddShader();

	void setTexture1(Texture& texture);
	void setTexture2(Texture& texture);

	void setMultiplier1(float multiplier);
	void setMultiplier2(float multiplier);
};

#endif