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
	if (t0x > t1x) std::swap(t0x, t1x);

	//y
	float t0y = (bmin.y - ray.origin.y) / ray.direction.y;
	float t1y = (bmax.y - ray.origin.y) / ray.direction.y;
	if (t0y > t1y) std::swap(t0y, t1y);

	//z
	float t0z = (bmin.z - ray.origin.z) / ray.direction.z;
	float t1z = (bmax.z - ray.origin.z) / ray.direction.z;
	if (t0z > t1z) std::swap(t0z, t1z);

	float tMin = std::max(t0x, t0y); //greatest min
	float tMax = std::min(t1x, t1y); //smallest max

	/*
	std::cout << "t0x: " << t0x << std::endl;
	std::cout << "t1y: " << t1y << std::endl;
	std::cout << "t0y: " << t0y << std::endl;
	std::cout << "t1x: " << t1x << std::endl;
	std::cout << "t0z: " << t0z << std::endl;
	std::cout << "t1z: " << t1z << std::endl;
	*/

	static float eps = 0.000001f;

	//if (t0x >= t1y + eps || t0y >= t1x + eps) return false;
	if (tMin >= t1z + eps || t0z >= tMax + eps) return false;
	if (t0z >= tMin) tMin = t0z;
	if (t1z <= tMax) tMax = t1z;
	if (tMin < 0 || tMax < 0) return false;

	outPoint1 = ray.origin + tMin * ray.direction;
	outPoint2 = ray.origin + tMax * ray.direction;

	return true;
}