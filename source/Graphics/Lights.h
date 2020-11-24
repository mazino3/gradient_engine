#ifndef GRAPHICS_LIGHTS_H
#define GRAPHICS_LIGHTS_H

#include <glm/vec3.hpp>

struct PositionalLight
{
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 spectacularColor;
	glm::vec3 direction;
};

struct DirectionalLight
{
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 spectacularColor;
	glm::vec3 position;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

#endif