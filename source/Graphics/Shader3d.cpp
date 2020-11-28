#include "Shader3d.h"
#include <string>


Shader3d::Shader3d() : Shader(ShaderInitType::Filename, "Assets/Shaders/Shader3d.vert", "Assets/Shaders/Shader3d.frag")
{}

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
	texture.bind(0);
}

void Shader3d::setMaterial(const Material& material, int index)
{
	std::string uniformPrefix = "materials[" + std::to_string(index) + "]";
	setUniform(uniformPrefix + ".emission", material.emission);
	setUniform(uniformPrefix + ".ambient", material.ambient);
	setUniform(uniformPrefix + ".diffuse", material.diffuse);
	setUniform(uniformPrefix + ".specular", material.specular);
	setUniform(uniformPrefix + ".shininess", material.shininess);
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

void Shader3d::setDirectionalLight(const DirectionalLight& light, int index)
{
	std::string uniformPrefix = "directionalLights[" + std::to_string(index) + "]";
	setUniform(uniformPrefix + ".direction", light.direction);
	setUniform(uniformPrefix + ".ambientColor", light.ambientColor);
	setUniform(uniformPrefix + ".diffuseColor", light.diffuseColor);
	setUniform(uniformPrefix + ".specularColor", light.specularColor);
}