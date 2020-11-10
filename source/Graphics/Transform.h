#ifndef GRAPHICS_TRANSFORM_H
#define GRAPHICS_TRANSFORM_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation; //around xyz
	glm::vec3 scale;

	glm::mat4x4 getWorldMatrix();
};

#endif