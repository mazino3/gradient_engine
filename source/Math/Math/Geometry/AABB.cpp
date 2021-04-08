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
	float t0x = (bmin.x - ray.origin.x) / ray.direction.x;
	float t1x = (bmax.x - ray.origin.x) / ray.direction.x;
	//if (txMax < txMin) std::swap(txMax, txMin);

	//y
	float t0y = (bmin.y - ray.origin.y) / ray.direction.y;
	float t1y = (bmax.y - ray.origin.y) / ray.direction.y;
	//if (tyMax < tyMin) std::swap(tyMax, tyMin);

	//z
	float t0z = (bmin.z - ray.origin.z) / ray.direction.z;
	float t1z = (bmax.z - ray.origin.z) / ray.direction.z;
	//if (tzMax < tzMin) std::swap(tzMax, tzMin);

	float tMin = std::max(t0x, t0y); //greatest min
	float tMax = std::min(t1x, t1y); //smallest max

	if (t0x > t1y || t0y > t1x) return false;
	if (tMin > t1z || t0z > tMax) return false;
	if (t0z > tMin) tMin = t0z;
	if (t1z < tMax) tMax = t1z;
	if (tMin < 0 || tMax < 0) return false;

	outPoint1 = ray.origin + tMin * ray.direction;
	outPoint2 = ray.origin + tMax * ray.direction;

	return true;
}