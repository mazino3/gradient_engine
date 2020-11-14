#ifndef GRAPHICS_SHADER_3D
#define GRAPHICS_SHADER_3D

#include "Shader.h"
#include "Texture.h"

struct Shader3d : Shader
{
	Shader3d();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	void setModelMatrix(const glm::mat4x4& matrix);
	void setDiffuseTexture(Texture& texture);
};

#endif