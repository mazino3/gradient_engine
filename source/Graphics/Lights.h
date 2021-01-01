#ifndef GRAPHICS_LIGHTS_H
#define GRAPHICS_LIGHTS_H

#include <glm/vec3.hpp>

struct DirectionalLight
{
	DirectionalLight();

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	glm::vec3 direction;

	bool shadowsEnabled;
};

struct PositionalLight
{
	PositionalLight();

	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
	glm::vec3 position;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	bool shadowsEnabled;
};

#endif