#include "AABB.h"

AABB::AABB() :
	position(glm::vec3(0, 0, 0)), size(glm::vec3(0, 0, 0))
{}

AABB::AABB(glm::vec3 position, glm::vec3 size) :
	position(position),
	size(size)
{}

bool AABB::intersectsWith(const Ray& ray)
{
	//todo: implement
}