#ifndef GRAPHICS_MATERIAL_H
#define GRAPHICS_MATERIAL_H

#include <glm/vec3.hpp>

struct Material
{
	glm::vec3 emission; //light produced by the material
	glm::vec3 ambient; //what part of ambient light is reflected
	glm::vec3 diffuse; //what part of diffuse light is scaterred
	glm::vec3 specular; //what part of specular light is scattered
	float shininess;

	Material() {}
	
	Material(glm::vec3 emission, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) :
		emission(emission),
		ambient(ambient),
		diffuse(diffuse),
		specular(specular) 
	{}
};

#endif