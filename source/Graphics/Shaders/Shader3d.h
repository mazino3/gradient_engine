#ifndef GRAPHICS_SHADER_3D
#define GRAPHICS_SHADER_3D

#include "Shader.h"
#include "../Texture.h"
#include "../CubeMap.h"
#include "../Material.h"
#include "../Lights.h"

struct Shader3d : Shader
{
	Shader3d();

	void setProjectionMatrix(const glm::mat4x4& matrix);
	void setViewMatrix(const glm::mat4x4& matrix);
	void setModelMatrix(const glm::mat4x4& matrix);
	void setNormalMatrix(const glm::mat4x4& matrix);

	void setDiffuseTexture(Texture& texture);
	void setNormalTexture(Texture& texture);
	void setEnvironmentMap(CubeMap& envMap);
	void setEnvironmentMapEnabled(bool enabled);
	void setNormalMapEnabled(bool enabled);
	void setMaterial(const Material& material, int index);
	void setCurrentMaterialIndex(int index);
	void setEyeDirection(const glm::vec3& eyeDirection);

	void setDirectionalLightsWithShadowsCount(int count);
	void setDirectionalLightWithShadow(const DirectionalLight& light, const glm::mat4x4 viewMatrix, Texture& depthTexture, int index);
	void setShadowDirLightViewProjection(const glm::mat4x4& matrix, int index);

	void setDirectionalLightsCount(int count);
	void setDirectionalLight(const DirectionalLight& light, const glm::mat4x4& viewMatrix, int index);
	
	void setPositionalLightsCount(int count);
	void setPositionalLight(const PositionalLight& light, int index);

	void setTextureScalingEnabled(bool textureScalingEnabled);
	void setTextureScale(const glm::vec3& textureScale);

	void bind() override;
};

#endif