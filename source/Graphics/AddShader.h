#ifndef GRAPHICS_ADD_SHADER_H
#define GRAPHICS_ADD_SHADER_H

#include "Shader.h"
#include "Texture.h"

struct AddShader : Shader
{
	AddShader();

	void setTexture1(Texture& texture);
	void setTexture2(Texture& texture);
};

#endif