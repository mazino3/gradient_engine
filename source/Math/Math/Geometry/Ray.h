#ifndef MATH_RAY_H
#define MATH_RAY_H

#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray() :
		origin(0, 0, 0),
		direction(1, 0, 0)
	{}

	Ray(glm::vec3 origin, glm::vec3 direction) :
		origin(origin),
		direction(direction)
	{}
};

#endif