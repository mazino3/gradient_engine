#ifndef MATH_PLANE_H
#define MATH_PLANE_H

#include <glm/vec3.hpp>
#include <Math/Geometry/Ray.h>

struct Plane
{
	glm::vec3 origin;
	glm::vec3 normal;

	Plane(const glm::vec3& origin, const glm::vec3& normal);

	bool intersectsWith(const Ray& ray);
	bool intersectsWith(const Ray& ray, glm::vec3& outPoint);

	static Plane PLANE_XY;
	static Plane PLANE_XZ;
	static Plane PLANE_YZ;
};

#endif