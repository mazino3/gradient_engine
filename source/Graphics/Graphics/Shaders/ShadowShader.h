#ifndef GRAPHICS_SHADOW_SHADER_H
#define GRAPHICS_SHADOW_SHADER_H

#include <Graphics/Shaders/Shader.h>

struct ShadowShader : Shader
{
	ShadowShader();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	void setModelMatrix(const glm::mat4x4& matrix);
};

#endif