#ifndef GRAPHICS_OUTLINE_ADD_SHADER_H
#define GRAPHICS_OUTLINE_ADD_SHADER_H

#include <Graphics/Shaders/Shader.h>
#include <Graphics/Texture.h>

struct OutlineAddShader : Shader
{
	OutlineAddShader();

	void setOutlineTexture(Texture& texture);
	void setScreenTexture(Texture& texture);
	void setOutlineColor(const glm::vec3& outlineColor);
};

#endif