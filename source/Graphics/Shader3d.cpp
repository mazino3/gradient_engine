#include "Shader3d.h"
#include <string>


Shader3d::Shader3d() : Shader(ShaderInitType::Filename, "Assets/Shaders/Shader3d.vert", "Assets/Shaders/Shader3d.frag")
{}

static const int DIFFUSE_TEXTURE_UNIT = 0;
static const int NORMAL_TEXTURE_UNIT = 1;
static const int ENV_MAP_TEXTURE_UNIT = 2;
static const int DEPTH_TEXTURE_UNIT = 3;

void Shader3d::setModelMatrix(const glm::mat4x4& matrix)
{
	setUniform("model", matrix);
}

void Shader3d::setProjectionMatrix(const glm::mat4x4& matrix)
{
	setUniform("projection", matrix);
}

void Shader3d::setViewMatrix(const glm::mat4x4& matrix)
{
	setUniform("view", matrix);
}

void Shader3d::setNormalMatrix(const glm::mat4x4& matrix)
{
	setUniform("normalTm", matrix);
}

void Shader3d::setDiffuseTexture(Texture& texture)
{
	texture.bind(DIFFUSE_TEXTURE_UNIT);
	setUniform("diffuseTex", DIFFUSE_TEXTURE_UNIT);
}

void Shader3d::setNormalTexture(Texture& texture)
{
	texture.bind(NORMAL_TEXTURE_UNIT);
	setUniform("normalTex", NORMAL_TEXTURE_UNIT);
}

void Shader3d::setEnvironmentMap(CubeMap& envMap)
{
	envMap.bind(ENV_MAP_TEXTURE_UNIT);
	setUniform("envMap", ENV_MAP_TEXTURE_UNIT);
}

void Shader3d::setEnvironmentMapEnabled(bool enabled)
{
	setUniform("envMapEnabled", enabled ? 1 : 0);
	if (!enabled)
	{
		setUniform("envMap", 2);
	}
}

void Shader3d::setNormalMapEnabled(bool enabled)
{
	setUniform("normalMapEnabled", enabled ? 1 : 0);
}

void Shader3d::setMaterial(const Material& material, int index)
{
	std::string uniformPrefix = "materials[" + std::to_string(index) + "]";
	setUniform(uniformPrefix + ".emission", material.emission);
	setUniform(uniformPrefix + ".ambient", material.ambient);
	setUniform(uniformPrefix + ".diffuse", material.diffuse);
	setUniform(uniformPrefix + ".specular", material.specular);
	setUniform(uniformPrefix + ".shininess", material.shininess);
	setUniform(uniformPrefix + ".alpha", material.alpha);
}

void Shader3d::setCurrentMaterialIndex(int index)
{
	setUniform("materialIndex", index);
}

void Shader3d::setEyeDirection(const glm::vec3& eyeDirection)
{
	setUniform("eyeDirection", eyeDirection);
}

void Shader3d::setDirectionalLightsCount(int count)
{
	setUniform("directionalLightsCount", count);
}

void Shader3d::setDirectionalLight(const DirectionalLight& light, const glm::mat4x4& viewMatrix, int index)
{
	std::string uniformPrefix = "directionalLights[" + std::to_string(index) + "]";
	glm::vec3 eyeSpaceDirection = glm::vec3(glm::mat4(glm::mat3(viewMatrix)) * glm::vec4(light.direction, 1.0f));
	setUniform(uniformPrefix + ".direction", eyeSpaceDirection);
	setUniform(uniformPrefix + ".ambientColor", light.ambientColor);
	setUniform(uniformPrefix + ".diffuseColor", light.diffuseColor);
	setUniform(uniformPrefix + ".specularColor", light.specularColor);
}

void Shader3d::setDirectionalLightsWithShadowsCount(int count)
{
	setUniform("directionalLightsWithShadowsCount", count);
}

void Shader3d::setDirectionalLightWithShadow(const DirectionalLight& light, const glm::mat4x4 viewMatrix, Texture& depthTexture, int index)
{
	std::string uniformPrefix = "directionalLightsWithShadows[" + std::to_string(index) + "]";
	glm::vec3 eyeSpaceDirection = glm::vec3(glm::mat4(glm::mat3(viewMatrix)) * glm::vec4(light.direction, 1.0f));
	setUniform(uniformPrefix + ".direction", eyeSpaceDirection);
	setUniform(uniformPrefix + ".ambientColor", light.ambientColor);
	setUniform(uniformPrefix + ".diffuseColor", light.diffuseColor);
	setUniform(uniformPrefix + ".specularColor", light.specularColor);

	int textureUnit = DEPTH_TEXTURE_UNIT + index;
	depthTexture.bind(textureUnit);
	setUniform("depthTextures[" + std::to_string(index) + "]", textureUnit);
}

void Shader3d::setPositionalLightsCount(int count)
{
	setUniform("positionalLightsCount", count);
}

void Shader3d::setPositionalLight(const PositionalLight& light, int index)
{
	std::string uniformPrefix = "positionalLights[" + std::to_string(index) + "]";
	setUniform(uniformPrefix + ".position", light.position);
	setUniform(uniformPrefix + ".ambientColor", light.ambientColor);
	setUniform(uniformPrefix + ".diffuseColor", light.diffuseColor);
	setUniform(uniformPrefix + ".specularColor", light.specularColor);
	setUniform(uniformPrefix + ".constantAttenuation", light.constantAttenuation);
	setUniform(uniformPrefix + ".linearAttenuation", light.linearAttenuation);
	setUniform(uniformPrefix + ".quadraticAttenuation", light.quadraticAttenuation);
}

void Shader3d::setTextureScalingEnabled(bool textureScalingEnabled)
{
	setUniform("textureScalingEnabled", textureScalingEnabled ? 1 : 0);
}

void Shader3d::setTextureScale(const glm::vec3& textureScale)
{
	setUniform("textureScale", textureScale);
}