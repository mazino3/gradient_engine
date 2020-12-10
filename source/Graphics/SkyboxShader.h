#ifndef GRAPHICS_SKYBOX_SHADER_H
#define GRAPHICS_SKYBOX_SHADER_H

#include "Shader.h"
#include "CubeMap.h"

struct SkyboxShader : Shader
{
	SkyboxShader();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	void setModelMatrix(const glm::mat4x4& matrix);

	void setSkyboxCubemap(CubeMap& cubemap);
};

#endif