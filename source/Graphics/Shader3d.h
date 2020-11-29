#ifndef GRAPHICS_SHADER_3D
#define GRAPHICS_SHADER_3D

#include "Shader.h"
#include "Texture.h"
#include "Material.h"
#include "Lights.h"

struct Shader3d : Shader
{
	Shader3d();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	void setModelMatrix(const glm::mat4x4& matrix);
	void setNormalMatrix(const glm::mat4x4& matrix);

	void setDiffuseTexture(Texture& texture);
	void setMaterial(const Material& material, int index);
	void setCurrentMaterialIndex(int index);
	void setEyeDirection(const glm::vec3& eyeDirection);

	void setDirectionalLightsCount(int count);
	void setDirectionalLight(const DirectionalLight& light, int index);
	void setPositionalLightsCount(int count);
	void setPositionalLight(const PositionalLight& light, int index);
};

#endif