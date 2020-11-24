#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include <glm/vec3.hpp>

struct Material
{
	glm::vec3 emission; //light produced by the material
	glm::vec3 ambient; //what part of ambient light is reflected
	glm::vec3 diffuse; //what part of diffuse light is scaterred
	glm::vec3 spectacular; //what part of spectacular light is scattered
	float shininess;
};

#endif