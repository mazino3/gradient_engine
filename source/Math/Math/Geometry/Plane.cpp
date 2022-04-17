#include "Plane.h"
#include <glm/ext.hpp>
#include <cmath>

Plane::Plane(const glm::vec3& origin, const glm::vec3& normal) :
	origin(origin),
	normal(normal)
{}

bool Plane::intersectsWith(const Ray& ray)
{
	glm::vec3 unused;
	return intersectsWith(ray, unused);
}

bool Plane::intersectsWith(const Ray& ray, glm::vec3& outPosition)
{
	static float eps = 0.00001f;
	if (std::abs(glm::dot(ray.direction, normal)) < eps) 
	{
		return false;
	}

	float t = glm::dot(origin - ray.origin, normal) / glm::dot(ray.direction, normal);
	if (t < -eps)
	{
		return false;
	}

	outPosition = ray.origin + ray.direction * t;

	return true;
}

Plane Plane::PLANE_XY(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
Plane Plane::PLANE_XZ(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
Plane Plane::PLANE_YZ(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));

