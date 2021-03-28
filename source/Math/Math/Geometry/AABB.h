#ifndef MATH_AABB_H
#define MATH_AABB_H

#include <glm/vec3.hpp>
#include <Math/Geometry/Ray.h>

struct AABB
{
	glm::vec3 position;
	glm::vec3 size;

	AABB();
	AABB(glm::vec3 position, glm::vec3 size);

	bool intersectsWith(const Ray& ray);
};

#endif