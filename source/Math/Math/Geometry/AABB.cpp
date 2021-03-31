#include <Math/Geometry/AABB.h>
#include <algorithm>

AABB::AABB() :
	position(glm::vec3(0, 0, 0)), size(glm::vec3(0, 0, 0))
{}

AABB::AABB(glm::vec3 position, glm::vec3 size) :
	position(position),
	size(size)
{}

bool AABB::intersectsWith(const Ray& ray)
{
	glm::vec3 unused;
	return intersectsWith(ray, unused, unused);
}

bool AABB::intersectsWith(const Ray& ray, glm::vec3& outPoint1, glm::vec3& outPoint2)
{
	glm::vec3 bmin = position - size / 2.0f;
	glm::vec3 bmax = position + size / 2.0f;
	
	//x
	float txMin = (bmin.x - ray.origin.x) / ray.direction.x;
	float txMax = (bmax.x - ray.origin.x) / ray.direction.x;
	if (txMax < txMin) std::swap(txMax, txMin);

	//y
	float tyMin = (bmin.y - ray.origin.y) / ray.direction.y;
	float tyMax = (bmax.y - ray.origin.y) / ray.direction.y;
	if (tyMax < tyMin) std::swap(tyMax, tyMin);

	//z
	float tzMin = (bmin.z - ray.origin.z) / ray.direction.z;
	float tzMax = (bmax.z - ray.origin.z) / ray.direction.z;
	if (tzMax < tzMin) std::swap(tzMax, tzMin);

	float tMin = std::max(txMin, tyMin); //greatest min
	float tMax = std::min(txMax, tyMax); //smallest max

	if (txMin > tyMax || tyMin > txMax) return false;
	if (tMin > tzMax || tzMin > tMax) return false;
	
	tMin = std::max(tMin, tzMin);
	tMax = std::min(tMax, tzMax);

	outPoint1 = ray.origin + tMin * ray.direction;
	outPoint2 = ray.origin + tMax * ray.direction;

	return true;
}